// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ShootEmUpGameState.generated.h"

/**
 * This class uses functions to calculate enemy count, idea is from YouTube -video i watched some times ago and got it from my older project.
 */
UCLASS()
class AShootEmUpGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AShootEmUpGameState();

	
protected:

	int32 Level;
	uint16 EnemyCountOnMap;


public:
	uint16 TotalEnemiesRemaining;
	


public:
	UFUNCTION(BlueprintCallable)
	int32 GetLevel();

	UINT16 GetTotalEnemiesRemaining();

	void IncreaseLevel();

	void SetTotalEnemiesRemaining(const uint16 EnemyCount);

	void EnemyKilled();




};
