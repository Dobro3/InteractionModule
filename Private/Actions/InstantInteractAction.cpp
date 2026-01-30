// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/


#include "Actions/InstantInteractAction.h"

#include "InteractHandlerComponent.h"

void UInstantInteractAction::StartInteraction_Implementation(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler)
{
	Super::StartInteraction_Implementation(InteractionComponent, InteractHandler);

	if (IsValid(InteractHandler) && InteractHandler->GetOwnerRole() == ROLE_Authority)
	{
		InteractHandler->EndInteraction(InteractionComponent);
	}
}
