// Created by Tommi Kekomäki, all code free to use for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "EnemyCharacterBase.generated.h"


/**
 * All AI Characters derive from this class
 * This Class has Gameplay Ability System -functions by Tranek's GAS-documentation or Epic Game's RPG-Demo, which are applied to my project needs.
 */
UCLASS()
class AEnemyCharacterBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEnemyCharacterBase();

protected:

	//hard pointer to AbilitySystemComponent
	UPROPERTY()
	class UASCBase* HardRefAbilitySystemComponent;

	// hard pointer to AttributeSetBase
	UPROPERTY()
	class UAttributeSetBase* HardRefAttributeSetBase;
	
	FDelegateHandle HealthChangedDelegateHandle;

	bool bIsAttacking;


	FName EnemyTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HealthBar")
	TSubclassOf<class UEnemyBar> EnemyBarClass;

	UPROPERTY()
	class UEnemyBar* EnemyBar;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "HealthBar")
	class UWidgetComponent* EnemyBarComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat R")
	class UBoxComponent* HandHitBoxR;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat L")
	class UBoxComponent* HandHitBoxL;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cbombat R")
		bool bHasCollisionSocketR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat L")
		bool bHasCollisionSocketL;

protected:
	
	virtual void BeginPlay() override;

	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);


protected:

	//Collision activators
	UFUNCTION(BlueprintCallable, Category = "Combat R")
	void ActivateCollisionR();
	UFUNCTION(BlueprintCallable, Category = "Combat R")
	void DeActivateCollisionR();
	UFUNCTION(BlueprintCallable, Category = "Combat L")
	void ActivateCollisionL();
	UFUNCTION(BlueprintCallable, Category = "Combat L")
	void DeActivateCollisionL();

	UFUNCTION(BlueprintCallable, Category = "Combat R")
	void AttachCollisionR();
	UFUNCTION(BlueprintCallable, Category = "Combat L")
	void AttachCollisionL();



};
