// Created by Tommi Kekomäki, all code free to use for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Demo/Demo.h"
#include "GameplayAbilityBase.generated.h"

/**
* 
* BaseClass for abilities
* 
 *  *  * This class has some Gameplay Ability System function's by Tranek's GAS Documentation. I always use these as a GAS-base functions for my projects that use Gameplay Ability System -plugin and adjust them a to my needs.
 * https://github.com/tranek/GASDocumentation
 *    I'm not sure what are Tranek's functions and what are functions created by me years ago i started experimenting with gas.
 */
UCLASS()
class UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:

UGameplayAbilityBase();

// Abilities with this set will automatically activate when the input is pressed
UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
EAbilityInputID AbilityInputID = EAbilityInputID::None;

// Value to associate an ability with an slot without tying it to an automatically activated input.
// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
EAbilityInputID AbilityID = EAbilityInputID::None;

// Tells an ability to activate immediately when its granted, used mostly in passives or as other abilities that activates on "Beginplay"
UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
bool ActivateAbilityOnGranted = false;
	
};
