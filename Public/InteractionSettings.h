// SPDX-License-Identifier: CC-BY-NC-4.0 GitHub@Dobro3 You are free to use, modify, and share this code for non-commercial purposes only. Selling this code or derivatives is not permitted. For details, see: https://creativecommons.org/licenses/by-nc/4.0/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "InteractionSettings.generated.h"

/**
 * Global settings for the Interaction system. 
 */
UCLASS()
class INTERACTIONMODULE_API UInteractionSettings : public UDeveloperSettings
{
	GENERATED_BODY()

protected:
	virtual FName GetCategoryName() const override { return FName(TEXT("Game")); }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	TEnumAsByte<ECollisionChannel> InteractionCollisionChannel;
};
