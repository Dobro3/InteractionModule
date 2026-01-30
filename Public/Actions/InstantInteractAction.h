// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/

#pragma once

#include "CoreMinimal.h"
#include "InteractAction.h"
#include "InstantInteractAction.generated.h"

/**
 * Interact action that doesn't need to be called continuously. Ends as soon as starts.
 */
UCLASS(Abstract, ClassGroup=Interaction)
class INTERACTIONMODULE_API UInstantInteractAction : public UInteractAction
{
	GENERATED_BODY()

protected:
	virtual void StartInteraction_Implementation(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler) override;
};
