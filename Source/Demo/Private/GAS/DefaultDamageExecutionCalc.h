// Created by Tommi Kekomäki, all code free to use for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DefaultDamageExecutionCalc.generated.h"

/**
 *  This class has some Gameplay Ability System function's by Tranek's GAS Documentation. I always use these as a GAS-base functions for my projects that use Gameplay Ability System -plugin and adjust them a to my needs.
 * https://github.com/tranek/GASDocumentation
 *    I'm not sure what are Tranek's functions and what are functions created by me years ago i started experimenting with gas.
 */
UCLASS()
class UDefaultDamageExecutionCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	UDefaultDamageExecutionCalc();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
