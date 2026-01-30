// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/


#include "InteractionComponent.h"

#include "InteractHandlerComponent.h"
#include "InteractionInterface.h"
#include "InteractionModule.h"
#include "InteractionSettings.h"

static TAutoConsoleVariable<bool> CVarInteractionDrawDebug(
	TEXT("Interaction.DrawDebug"),
	false,
	TEXT("Draws debug info for interaction system."),
	ECVF_Default
);

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

AController* UInteractionComponent::GetOwnerController() const
{
	if (IsValid(GetOwner()))
	{
		return GetOwner()->GetInstigatorController();
	}

	return nullptr;
}

APlayerController* UInteractionComponent::GetOwnerPlayerController() const
{
	if (IsValid(GetOwner()))
	{
		return Cast<APlayerController>(GetOwner()->GetInstigatorController());
	}

	return nullptr;
}


void UInteractionComponent::TryInteractWithCurrentTarget()
{
	/// We call for try interact even if locally we think it might not want it, cause client might not be right on that part.
	if (IsValid(CurrentTarget))
	{
		TryInteractWithHandler(CurrentTarget);
	}
}

void UInteractionComponent::TryInteractWithHandler_Implementation(UInteractHandlerComponent* InteractHandler)
{
	if (IsValid(InteractHandler))
	{
		InteractHandler->TryInteract(this);
	}
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	if ((GetOwnerRole() == ROLE_Authority || GetOwnerRole() == ROLE_AutonomousProxy) && !CheckSetupCorrectly())
	{
		UE_LOG(LogInteractionModule, Error, TEXT("%s setup incorrectly! Outer instigator should be a valid controller! Owner actor : %s"), *GetName(), *GetNameSafe(GetOwner()));
	}
}


void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldLookForInteract())
	{
		FindInteractTarget();
	}
}

void UInteractionComponent::FindInteractTarget()
{
	APlayerController* OwningPlayer = GetOwnerPlayerController();
	if (!IsValid(OwningPlayer))
	{
		UE_LOG(LogInteractionModule, Warning, TEXT("%s TraceForInteract called not in player controller instigator (Owner: %s) which doesn't have sense now! Aborting..."), *GetName(), *GetNameSafe(GetOwner()));
		return;
	}

	APlayerCameraManager* CameraManager = OwningPlayer->PlayerCameraManager;
	if (!IsValid(CameraManager))
	{
		/// no log, some weird situation, not yet decided whether it's ok or not.
		return;
	}

	FVector CameraLocation; FRotator CameraRotation;
	CameraManager->GetCameraViewPoint(CameraLocation, CameraRotation);

	/// No need to check, it will always exist.
	ECollisionChannel InteractionChannel = GetDefault<UInteractionSettings>()->InteractionCollisionChannel;

	const FVector TraceEnd = CameraLocation + CameraRotation.Vector() * GetTraceDistance();
	
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	FCollisionResponseParams ResponseParams;
	
	GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, TraceEnd, InteractionChannel, Params);

	UInteractHandlerComponent* InteractHandler = TryGetInteractHandler(Hit.GetActor());
	const bool bReadyForInteract = IsTargetReadyForInteract(InteractHandler); 

	if (CVarInteractionDrawDebug.GetValueOnAnyThread())
	{
		DrawDebugTrace(Hit, CameraLocation, TraceEnd, CameraRotation, bReadyForInteract);
	}

	SetCurrentTarget(InteractHandler);
}

bool UInteractionComponent::CheckSetupCorrectly() const
{
	return IsValid(GetOwnerController());
}

bool UInteractionComponent::ShouldLookForInteract() const
{
	const APlayerController* OwningPlayer = GetOwnerPlayerController();
	if (!IsValid(OwningPlayer))
	{
		return false;
	}

	return OwningPlayer->IsLocalController();
}

void UInteractionComponent::DrawDebugTrace(const FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd,
	const FRotator& CameraRotation, bool bCanInteract)
{
#if !UE_BUILD_SHIPPING
	/// Trace from center of screen would be invisible, need to adjust a bit.
	const FVector DrawStartOffset = CameraRotation.RotateVector(FVector::RightVector) * 3.f;
	const FColor TraceColor = bCanInteract ? FColor::Green : FColor::Red;

	/// TODO: different color depending on interaction possibility.
	DrawDebugLine(GetWorld(), TraceStart + DrawStartOffset, TraceEnd, TraceColor, false, -1, 0, 1);

	if (IsValid(HitResult.GetActor()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, TraceColor, FString::Printf(TEXT("Interact target: %s"), *GetNameSafe(HitResult.GetActor())));
	}
#endif
}

UInteractHandlerComponent* UInteractionComponent::TryGetInteractHandler(const AActor* TargetActor) const
{
	 return IsValid(TargetActor) && TargetActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()) ?
		IInteractionInterface::Execute_GetInteractableComponent(TargetActor) : nullptr;
}

bool UInteractionComponent::IsTargetReadyForInteract(UInteractHandlerComponent* InteractTarget)
{
	return IsValid(InteractTarget) ? InteractTarget->CanInteract(this) : false;
}

void UInteractionComponent::SetCurrentTarget(UInteractHandlerComponent* NewTargetActor)
{
	if (CurrentTarget != NewTargetActor)
	{
		if (IsValid(CurrentTarget))
		{
			CurrentTarget->SetNewAimer(nullptr);
		}
		
		CurrentTarget = NewTargetActor;
		
		if (IsValid(CurrentTarget))
		{
			CurrentTarget->SetNewAimer(this);
		}
	}
}

