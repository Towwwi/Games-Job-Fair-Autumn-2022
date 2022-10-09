// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Character/Enemy/EnemyCharacterBase.h"
#include "ShootEmUpGamemode.generated.h"

/**
 * Idea of the enemy calculation is from YouTube video i watched some times ago and got it from my old project.
 */
UCLASS()
class AShootEmUpGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
		AShootEmUpGamemode();
	
		TArray<class AEnemySpawner*> EnemySpawners;


protected:
		
		UPROPERTY(EditAnywhere, Category = "Enemy")
		TSubclassOf<class AEnemyCharacterBase> RandomEnemy;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TArray<TSubclassOf<AEnemyCharacterBase>> AllEnemyTypes;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TArray<TSubclassOf<AEnemyCharacterBase>> enemies; 
		


		FTimerHandle SpawnTimeHandle;

		UPROPERTY(EditAnywhere)
		USoundBase* SwitchLevelSound;

		
		class AShootEmUpGameState* ShootEmUpGameState;

		uint16 EnemiesRemaining;




protected:
		
		void SpawnEnemy();

		void CalculateEnemyCount();

		void PlaySwitchLevelSound();

		void AddEnemyToArray();

		UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "LevelChange"))
		void DoAfterChangeLevel();

		UFUNCTION(BlueprintCallable)
		AShootEmUpGameState* GetOurGameState();
public:
		void EnemyKilled();

protected:

		virtual void BeginPlay() override;
};
