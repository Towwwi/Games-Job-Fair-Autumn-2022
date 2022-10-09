// Created by Tommi Kekomäki, all code free to use for educational purposes

#include "ShootEmUpGameState.h"

//Constructor
AShootEmUpGameState::AShootEmUpGameState()
{
	Level = 1;
	EnemyCountOnMap = 0;

	TotalEnemiesRemaining = 4;
}

//LevelGetter
int32 AShootEmUpGameState::GetLevel()
{
	return Level;
}

//EnemiesRemainingGetter
UINT16 AShootEmUpGameState::GetTotalEnemiesRemaining()
{
	UE_LOG(LogTemp, Warning, TEXT("TotalEnemiesRemaining: %d"), TotalEnemiesRemaining);
	return TotalEnemiesRemaining;

}

//Add to Level
void AShootEmUpGameState::IncreaseLevel()
{
	++Level;


	UE_LOG(LogTemp, Warning, TEXT("Increased lvl"));
}

// EnemyCount = Enemies remaining
void AShootEmUpGameState::SetTotalEnemiesRemaining(const uint16 EnemyCount)
{
	TotalEnemiesRemaining = EnemyCount;
}

//Decrease enemies remaining
void AShootEmUpGameState::EnemyKilled()
{
	--TotalEnemiesRemaining;
	UE_LOG(LogTemp, Warning, TEXT("Enemy count on map: d%"), EnemyCountOnMap);
}


