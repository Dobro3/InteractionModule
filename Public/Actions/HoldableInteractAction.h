// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/

#pragma once

#include "CoreMinimal.h"
#include "InteractAction.h"
#include "HoldableInteractAction.generated.h"

/**
 * Base action that runs while interacted by InteractionComponent.
 */
UCLASS()
class INTERACTIONMODULE_API UHoldableInteractAction : public UInteractAction
{
	GENERATED_BODY()

protected:
	virtual void StartInteraction_Implementation(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler) override;
	virtual void EndInteraction_Implementation(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(BlueprintReadWrite, Replicated, Category=Interaction)
	TObjectPtr<UInteractionComponent> CurrentInteractor;
};
