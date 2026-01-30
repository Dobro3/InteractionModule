// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InteractionCondition.generated.h"

class UInteractHandlerComponent;
class UInteractionComponent;

/**
 * Interaction condition for InteractableComponent to use to decide if interaction is available.
 * Might be helpful as a separate logic for conditions to avoid code duplication between classes.
 * Also easier for Game design to set up : programmers might provide logic parts and they can build it as blocks.
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew, ClassGroup=Interaction)
class INTERACTIONMODULE_API UInteractionCondition : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool CanInteract(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler);
	virtual bool CanInteract_Implementation(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler) { return false; }

protected:
	virtual bool IsSupportedForNetworking() const override { return true; }
};
