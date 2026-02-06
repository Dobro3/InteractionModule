// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/


#include "Actions/HoldableInteractAction.h"

#include "InteractionComponent.h"
#include "Net/UnrealNetwork.h"

void UHoldableInteractAction::StartInteraction_Implementation(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler)
{
	Super::StartInteraction_Implementation(InteractionComponent, InteractHandler);

	CurrentInteractor = InteractionComponent;
}

void UHoldableInteractAction::EndInteraction_Implementation(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler)
{
	if (CurrentInteractor == InteractionComponent && IsValid(CurrentInteractor))
	{
		Super::EndInteraction_Implementation(InteractionComponent, InteractHandler);

		CurrentInteractor = nullptr;
	}
}

void UHoldableInteractAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHoldableInteractAction, CurrentInteractor);
}
