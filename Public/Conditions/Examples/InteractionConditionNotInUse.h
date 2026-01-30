// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/

#pragma once

#include "CoreMinimal.h"
#include "Conditions/InteractionCondition.h"
#include "InteractionConditionNotInUse.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIONMODULE_API UInteractionConditionNotInUse : public UInteractionCondition
{
	GENERATED_BODY()
	
protected:
	virtual bool CanInteract_Implementation(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler) override;
};
