// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/

#pragma once

#include "CoreMinimal.h"
#include "Conditions/InteractionCondition.h"
#include "InteractionConditionAlwaysCan.generated.h"

/**
 * Condition that always allows to interact.
 */
UCLASS(Blueprintable, BlueprintType)
class INTERACTIONMODULE_API UInteractionConditionAlwaysCan : public UInteractionCondition
{
	GENERATED_BODY()

protected:
	virtual bool CanInteract_Implementation(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler) override;
};
