// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GAS/AttributeSetBase.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDyingDelegate, ACharacterBase*, Character);

 // *  This class has some Gameplay Ability System function's by Tranek's GAS Documentation. I always use these as a GAS-base functions for my projects that use Gameplay Ability System -plugin and adjust them a to my needs.
 // * https://github.com/tranek/GASDocumentation

UCLASS()
class ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);


public:	
	bool IsAlive() const;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//////# DEATH #//////

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visuals")
	UAnimMontage* DeathMontage;
	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintAssignable, Category = "Dying")
	FDyingDelegate OnCharacterDied;

	virtual void Die();

	virtual void EnemyDie();

	UFUNCTION(BlueprintCallable, Category = "Dying")
	virtual void FinishDying();

protected:

	//////# ASC AND ATTRIBUTES #//////
	TWeakObjectPtr<class UASCBase> AbilitySystemComponent;
	TWeakObjectPtr<class UAttributeSetBase> AttributeSetBase;

	bool bDeathMontagePlayed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Items To Dro pOn Death")
	TArray<TSubclassOf<class AActor>> ItemsToDrop;

	TSubclassOf<class AActor> RandomItem;

	virtual void DropItems();

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterBase // Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbilityBase>> CharacterAbilities;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual void AddNewAbility(TSubclassOf<UGameplayAbilityBase> NewAbility);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual void AddNewAbilities(TArray<TSubclassOf<UGameplayAbilityBase>> NewAbilities);

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	virtual void InitializeAttributes();

	class AShootEmUpGamemode* OurGameMode;

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterBase // Visuals")
	FText CharacterName;

	/**
	* Attribute Setters
	* These change the Attribute's Base Value.
	*/
	virtual void SetHealth(float Health);
	virtual void SetMana(float Mana);


	//////# GETTERS #//////
	UFUNCTION(BlueprintCallable, Category = "CharacterBase // Abilities")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "CharacterBase // Abilities")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "CharacterBase // Abilities")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "CharacterBase // Abilities")
	float GetMaxMana() const;


public:
	// Switch on AbilityID to return individual ability levels. 
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual int32 GetAbilityLevel(EAbilityInputID AbilityID) const;


	UFUNCTION(BlueprintCallable, Category = "Level")
	int32 GetCharacterLevel() const;
};
