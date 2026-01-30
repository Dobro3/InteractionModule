// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/


#include "InteractionHelpers.h"

#include "InteractHandlerComponent.h"
#include "InteractionInterface.h"

UInteractHandlerComponent* UInteractionHelpers::TryGetInteractHandler(const AActor* TargetActor)
{
	return IsValid(TargetActor) && TargetActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()) ?
		IInteractionInterface::Execute_GetInteractableComponent(TargetActor) : nullptr;
}

bool UInteractionHelpers::IsTargetReadyForInteract(UInteractionComponent* InteractionComponent, UInteractHandlerComponent* InteractTarget)
{
	return IsValid(InteractTarget) ? InteractTarget->CanInteract(InteractionComponent) : false;
}
