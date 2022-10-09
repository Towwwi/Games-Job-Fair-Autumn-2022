// Created by Tommi Kekomäki, all code free to use for educational purposes
#pragma once

#include "CoreMinimal.h"
#include "Demo/Private/GAS/ASCBase.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"



/**
 * 
 * This class has some function's by Tranek's GAS Documentation. I always use these as a GAS-base functions for projects that use Gameplay Ability System -plugin and adjust them  to my needs.
 * https://github.com/tranek/GASDocumentation
 *    I'm not sure what are Tranek's functions and what are functions created by me years ago i started experimenting with gas.
 */
UCLASS()
class APlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	APlayerStateBase();

	// GETTERS
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	class UAttributeSetBase* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState // Getters")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState // Getters")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState // Getters")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "PlayerState // Getters")
	float GetMaxMana() const;

protected:
	
	//Osoitin omaan ASC
	UPROPERTY()
	class UASCBase* ASC;

	//Osoitin AttributeSetBase
	UPROPERTY()
	class UAttributeSetBase* AttributeSetBase;

	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);

	virtual void ManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);

};
