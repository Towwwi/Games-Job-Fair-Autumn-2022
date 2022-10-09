// Created by Tommi Kekomäki, all code free to use for educational purposes
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ASCBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UASCBase*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);

/**
 * This class has some Gameplay Ability System function's by Tranek's GAS Documentation. I always use these as a GAS-base functions for my projects that use Gameplay Ability System -plugin and adjust them a to my needs.
 * I'm not sure what are Tranek's functions and what are functions created by me years ago i started experimenting with gas.
 * https://github.com/tranek/GASDocumentation
 */
UCLASS()
class DEMO_API UASCBase : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamage;

	//Called from DamageExecution. Broadcasts on ReceivedDamage whenever this ASC receives damage.
	virtual void ReceiveDamage(UASCBase* SourceASC, float UnmitigatedDamage, float MitigatedDamage);
};
