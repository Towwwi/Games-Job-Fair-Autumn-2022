// Created by Tommi Kekomäki, all code free to use for educational purposes


#include "Items/NewWeaponBase.h"
#include "GAS/ASCBase.h"
#include "GAS/GameplayAbilityBase.h"
#include "Components/CapsuleComponent.h"
#include "Items/ItemBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Hero/HeroCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Character/Hero/PlayerControllerBase.h"
#include "Kismet/KismetSystemLibrary.h"


ANewWeaponBase::ANewWeaponBase()
{

	WeaponState = EWeaponState::EWS_Pickup;

}

FORCEINLINE void ANewWeaponBase::SetWeaponState(EWeaponState State)
{

}


//Abilities are used to give new abilities to character
TArray<TSubclassOf<UGameplayAbilityBase>> ANewWeaponBase::GetAbilities()
{
	return Abilities;
}
