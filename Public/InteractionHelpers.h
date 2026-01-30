// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InteractionHelpers.generated.h"

class UInteractHandlerComponent;
class UInteractionComponent;

/**
 * Helpers functions for the Interaction system.
 */
UCLASS()
class INTERACTIONMODULE_API UInteractionHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/// Correct access to an actor's Interact Handler.
	UFUNCTION(BlueprintCallable, Category=Interaction)
	static UInteractHandlerComponent* TryGetInteractHandler(const AActor* TargetActor);

	/// Check if specific Handler ready to interact with specific interactor.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category=Interaction)
	static bool IsTargetReadyForInteract(UInteractionComponent*InteractionComponent, UInteractHandlerComponent* InteractTarget);
};
