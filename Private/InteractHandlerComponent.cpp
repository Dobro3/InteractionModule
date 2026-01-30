// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/


#include "InteractHandlerComponent.h"

#include "Conditions/InteractionCondition.h"
#include "InteractionComponent.h"
#include "Actions/InteractAction.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"


UInteractHandlerComponent::UInteractHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

bool UInteractHandlerComponent::TryInteract(UInteractionComponent* InteractionComponent)
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		return false;
	}

	if (CanInteract(InteractionComponent))
	{
		CallInteractInternal(InteractionComponent);
		return true;
	}

	return false;
}

void UInteractHandlerComponent::EndInteraction(UInteractionComponent* InteractionComponent)
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		return;
	}

	CallEndInteractInternal(InteractionComponent);
}

void UInteractHandlerComponent::CallInteractInternal_Implementation(UInteractionComponent* InteractionComponent)
{
	if (IsValid(InteractAction))
	{
		InteractAction->StartInteraction(InteractionComponent, this);
	}

	OnInteractStarted.Broadcast(InteractionComponent, this);
}

void UInteractHandlerComponent::CallEndInteractInternal_Implementation(UInteractionComponent* InteractionComponent)
{
	if (IsValid(InteractAction))
	{
		InteractAction->EndInteraction(InteractionComponent, this);
	}

	OnInteractEnded.Broadcast(InteractionComponent, this);
}

void UInteractHandlerComponent::SetInteractionCondition(UInteractionCondition* NewCondition)
{
	/// No checks for now.
	InteractionCondition = NewCondition;
}

void UInteractHandlerComponent::SetInteractAction(UInteractAction* NewAction)
{
	/// No checks for now.
	InteractAction = NewAction;
}

void UInteractHandlerComponent::SetNewAimer(UInteractionComponent* NewAimer)
{
	if (NewAimer != CurrentAimer)
	{
		CurrentAimer = NewAimer;
		OnAimChanged.Broadcast(CurrentAimer);
	}
}

void UInteractHandlerComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInteractHandlerComponent, InteractAction);
	DOREPLIFETIME(UInteractHandlerComponent, InteractionCondition);
}

bool UInteractHandlerComponent::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch,
	FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (IsValid(InteractAction))
	{
		bWroteSomething |= Channel->ReplicateSubobject(InteractAction, *Bunch, *RepFlags);
	}
	if (IsValid(InteractionCondition))
	{
		bWroteSomething |= Channel->ReplicateSubobject(InteractionCondition, *Bunch, *RepFlags);
	}

	return bWroteSomething;
}

bool UInteractHandlerComponent::CanInteract_Implementation(UInteractionComponent* InteractionComponent)
{
	if (!IsValid(InteractionCondition) || !IsValid(InteractAction))
	{
		return false;
	}

	return InteractionCondition->CanInteract(InteractionComponent, this) && InteractAction->CanInteract(InteractionComponent, this);
}


