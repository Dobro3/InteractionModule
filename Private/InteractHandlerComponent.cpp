// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/


#include "InteractHandlerComponent.h"

#include "Conditions/InteractionCondition.h"
#include "InteractionComponent.h"
#include "Actions/InteractAction.h"


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

void UInteractHandlerComponent::CallInteractInternal_Implementation(UInteractionComponent* InteractionComponent)
{
	if (IsValid(InteractAction))
	{
		InteractAction->StartInteraction(InteractionComponent, this);
	}

	OnInteractStarted.Broadcast(InteractionComponent, this);
}

void UInteractHandlerComponent::SetInteractionCondition(UInteractionCondition* NewCondition)
{
	/// No checks for now.
	InteractionCondition = NewCondition;
}

void UInteractHandlerComponent::SetInteractionAction(UInteractAction* NewAction)
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

bool UInteractHandlerComponent::CanInteract_Implementation(UInteractionComponent* InteractionComponent)
{
	if (!IsValid(InteractionCondition))
	{
		return false;
	}

	return InteractionCondition->CanInteract(InteractionComponent, this);
}


