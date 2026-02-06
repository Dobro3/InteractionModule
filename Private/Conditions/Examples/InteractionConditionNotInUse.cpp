// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/


#include "Conditions/Examples/InteractionConditionNotInUse.h"

#include "InteractHandlerComponent.h"
#include "Actions/InteractAction.h"

bool UInteractionConditionNotInUse::CanInteract_Implementation(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler)
{
	if (IsValid(InteractHandler) && IsValid(InteractHandler->GetInteractAction()))
	{
		return !InteractHandler->GetInteractAction()->GetIsRunning();
	}

	return false;
}
