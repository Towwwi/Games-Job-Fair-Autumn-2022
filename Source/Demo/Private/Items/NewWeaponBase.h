// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "Demo/Demo.h"
#include "Items/ItemBase.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "NewWeaponBase.generated.h"


//All weapons derive from this class

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponAmmoChangedDelegate, int32, OldValue, int32, NewValue);


// Weapon's current state
UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Pickup UMETA(DisplayName = "Pickup"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Max UMETA(DisplayName = "DefaultMAX")
};



UCLASS()
class ANewWeaponBase : public AItemBase
{
	GENERATED_BODY()

public:
	
	ANewWeaponBase();

protected:

	// Weapon State
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	EWeaponState WeaponState;

	//FORCEINLINE void SetWeaponState(EWeaponState) { WeaponState = WeaponState; }
	FORCEINLINE void SetWeaponState(EWeaponState State);
	FORCEINLINE EWeaponState GetWeaponState() { return WeaponState; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class USoundCue* EquipWeaponSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbilityBase>> Abilities;

	UFUNCTION(BlueprintCallable)
 	TArray<TSubclassOf<UGameplayAbilityBase>> GetAbilities();
};
