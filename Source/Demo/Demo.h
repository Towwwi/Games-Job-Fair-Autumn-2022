// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

 #define ACTOR_ROLE_FSTRING *(FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"), true)->GetNameStringByValue(GetLocalRole()))
 #define GET_ACTOR_ROLE_FSTRING(Actor) *(FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"), true)->GetNameStringByValue(Actor->GetLocalRole()))

#define COLLISION_PICKUP						ECollisionChannel::ECC_GameTraceChannel4
#define COLLISION_INTERACTABLE					ECollisionChannel::ECC_GameTraceChannel5


//Used for GAS input system

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	
	// !! DisplayName doesn't matter !!

	

	// None
	None			UMETA(DisplayName = "None"),
	// Confirm
	Confirm			UMETA(DisplayName = "Confirm"),
	// Cancel
	Cancel			UMETA(DisplayName = "Cancel"),
	// 1 LMB
	Ability1		UMETA(DisplayName = "Ability1"),
	// 2 RMB
	Ability2		UMETA(DisplayName = "Ability2"),
	// 3 Q
	Ability3		UMETA(DisplayName = "Ability3"),
	// 4 E
	Ability4		UMETA(DisplayName = "Ability4"),
	// 5 R
	Ability5		UMETA(DisplayName = "Ability5"),
	// 6 F
	Ability6		UMETA(DisplayName = "Ability6"),
	// 7 1
	Ability7		UMETA(DisplayName = "Ability7"),
	// 8 2
	Ability8		UMETA(DisplayName = "Ability8"),
	// 9 3
	Ability9		UMETA(DisplayName = "Ability9"),
	// 12 4
	Ability10		UMETA(DisplayName = "Ability10"),
	// 13 5
	Ability11		UMETA(DisplayName = "Ability11"),
	// 14 6
	Ability12		UMETA(DisplayName = "Ability12"),
	// Dodge Shift
	Dodge			UMETA(DisplayName = "Dodge"),
	// Sprint CTRL
	Sprint			UMETA(DisplayName = "Sprint"),
	// Jump
	Jump			UMETA(DisplayName = "Jump")
};