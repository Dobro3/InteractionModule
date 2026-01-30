// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractHandlerComponent.generated.h"


class UInteractAction;
class UInteractionComponent;
class UInteractionCondition;

UCLASS(ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class INTERACTIONMODULE_API UInteractHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractHandlerComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interaction)
	bool CanInteract(UInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = Interaction)
	bool TryInteract(UInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = Interaction)
	void EndInteraction(UInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintCosmetic, Category = Interaction)
	FORCEINLINE UInteractionComponent* GetCurrentAimer() const { return CurrentAimer; }

	UFUNCTION(NetMulticast, Reliable)
	void CallInteractInternal(UInteractionComponent* InteractionComponent);
	
	UFUNCTION(NetMulticast, Reliable)
	void CallEndInteractInternal(UInteractionComponent* InteractionComponent);

	UFUNCTION(BlueprintSetter)
	void SetInteractionCondition(UInteractionCondition* NewCondition);

	UFUNCTION(BlueprintSetter)
	void SetInteractAction(UInteractAction* NewAction);

	UFUNCTION(BlueprintGetter)
	FORCEINLINE UInteractAction* GetInteractAction() const { return InteractAction; } 

	void SetNewAimer(UInteractionComponent* NewAimer);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	
public:
	/// Called locally when someone start/end aiming on this for decorative purposes.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAimChanged, UInteractionComponent*, NewCurrentAimer);
	UPROPERTY(BlueprintAssignable)
	FOnAimChanged OnAimChanged;

	/// Event to optionally bind to call custom logic on start interact.
	/// Called on server and all clients.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractSignature, UInteractionComponent*, InteractCaller, UInteractHandlerComponent*, InteractHandler);
	UPROPERTY(BlueprintAssignable)
	FOnInteractSignature OnInteractStarted;

	/// Event to optionally bind to call custom logic on end interact.
	/// Called on server and all clients if needed.
	UPROPERTY(BlueprintAssignable)
	FOnInteractSignature OnInteractEnded;
	
protected:
	/// Condition to check if it is ready to interact.
	UPROPERTY(EditAnywhere, Instanced, Replicated, BlueprintSetter=SetInteractionCondition)
	TObjectPtr<UInteractionCondition> InteractionCondition;

	/// Action to call when interacted. 
	UPROPERTY(EditAnywhere, BlueprintGetter=GetInteractAction, BlueprintSetter=SetInteractAction, Replicated, Instanced)
	TObjectPtr<UInteractAction> InteractAction;

	/// Who currently wants to interact with it (aim at it).
	/// Cosmetic.
	UPROPERTY(Transient, BlueprintGetter=GetCurrentAimer, Category = Interaction)
	TObjectPtr<UInteractionComponent> CurrentAimer;

};
