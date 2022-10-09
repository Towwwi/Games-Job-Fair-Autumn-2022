// Created by Tommi Kekomäki, all code free to use for educational purposes
#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Items/ItemBase.h"
#include "Items/NewWeaponBase.h"
#include "Demo/Private/GAS/ASCBase.h"
#include "AbilitySystemInterface.h"
#include "HeroCharacter.generated.h"

/**
 * Class uses default UE4 movement functions
 * 
 * This class has some function's by Tranek's GAS Documentation. I always use these as a GAS-base functions for projects that use Gameplay Ability System -plugin and adjust them a little to my needs.
 * https://github.com/tranek/GASDocumentation
 *    I'm not sure what are Tranek's functions and what are functions created by me years ago i started experimenting with gas.
 */
UCLASS()
class AHeroCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	AHeroCharacter();

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	bool bASCInputBound = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsAttacking = false;



protected:

	virtual void OnRep_PlayerState() override;

	// Called from both SetupPlayerInputComponent and OnRep_PlayerState because of a potential race condition where the PlayerController might
	// call ClientRestart which calls SetupPlayerInputComponent before the PlayerState is repped to the client so the PlayerState would be null in SetupPlayerInputComponent.
	// Conversely, the PlayerState might be repped before the PlayerController calls ClientRestart so the Actor's InputComponent would be null in OnRep_PlayerState.
	void BindASCInput();

	// DEFAULT MOVEMENT SETUP
public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }



// Weapon and pickups
public:

	void SetEquippedWeapon(ANewWeaponBase* WeaponToset);
	FORCEINLINE ANewWeaponBase* GetEquippedWeapon() { return EquippedWeapon; }
	FORCEINLINE void SetActiveOverlappingItem(AItemBase* Pickup) { ActiveOverlappingItem = Pickup; }



	// ITEMS AND WEAPONS
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	class ANewWeaponBase* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	class AItemBase* ActiveOverlappingItem;


};
