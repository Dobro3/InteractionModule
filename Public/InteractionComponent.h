// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class UInteractHandlerComponent;
/// Interaction component that Must be inside a Player controller.
UCLASS(ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class INTERACTIONMODULE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Interaction)
	AController* GetOwnerController() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Interaction)
	APlayerController* GetOwnerPlayerController() const;

	UFUNCTION(BlueprintGetter)
	float GetTraceDistance() const { return TraceDistance; }

	UFUNCTION(BlueprintSetter)
	void SetTraceDistance(const float InTraceDistance) { TraceDistance = InTraceDistance; }

	UFUNCTION(BlueprintCallable, Category = Interaction)
	void TryInteractWithCurrentTarget();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = Interaction)
	void TryInteractWithHandler(UInteractHandlerComponent* InteractHandler);
	
protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void FindInteractTarget();

	virtual bool CheckSetupCorrectly() const;

	virtual bool ShouldLookForInteract() const;

	void DrawDebugTrace(const FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd, const FRotator& CameraRotation, bool bCanInteract);

	/// Check if this target possibly can be interacted with.
	UInteractHandlerComponent* TryGetInteractHandler(const AActor* TargetActor) const;
	
	/// Check if this target actually wants to interact.
	bool IsTargetReadyForInteract(UInteractHandlerComponent* InteractTarget);

	void SetCurrentTarget(UInteractHandlerComponent* NewTargetActor);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintGetter=GetTraceDistance, BlueprintSetter=SetTraceDistance, Category = Interaction)
	float TraceDistance = 1000.f;

	UPROPERTY(Transient, BlueprintReadOnly, Category = Interaction)
	TObjectPtr<UInteractHandlerComponent> CurrentTarget;
};
