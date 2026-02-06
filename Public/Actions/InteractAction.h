// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InteractAction.generated.h"

class UInteractHandlerComponent;
class UInteractionComponent;

/**
 * Basic class for interaction actions.
 * Might be helpful to prevent code duplication as a single chunk of reusable logic.
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract, Blueprintable, BlueprintType, ClassGroup=(Interaction))
class INTERACTIONMODULE_API UInteractAction : public UObject
{
	GENERATED_BODY()

public:
	/// Starts an interaction. Might end as soon as it was started or continue in time.
	UFUNCTION(BlueprintNativeEvent, Category=Interaction)
	void StartInteraction(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler);

	/// Ends an interaction signalizing that it is no more active.
	UFUNCTION(BlueprintNativeEvent, Category=Interaction)
	void EndInteraction(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractHandler);

	UFUNCTION(BlueprintGetter)
	FORCEINLINE bool GetIsRunning() const { return bIsRunning; }
	
protected:
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(Replicated, BlueprintGetter=GetIsRunning)
	bool bIsRunning = false;
};
