// Created by Tommi Kekomäki, all code free to use for educational purposes

#include "ShootEmUpGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "GameMechanics/EnemySpawner.h"
#include "ShootEmUpGameState.h"
#include "TimerManager.h"
#include "Character/Enemy/EnemyCharacterBase.h"
#include "ShootEmUpGamemode.h"

AShootEmUpGamemode::AShootEmUpGamemode()
{
	EnemiesRemaining = 1;


}


//Find all spawners and setup timers for spawning the enemies + call SpawnEnemy
void AShootEmUpGamemode::BeginPlay()
{

	UE_LOG(LogTemp, Warning, TEXT("Starting Gmaemode"));

	Super::BeginPlay();
	ShootEmUpGameState = GetGameState<AShootEmUpGameState>();

	// Find all spawners
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), TempActors);

	for (AActor* Actor : TempActors)
	{
		if (AEnemySpawner* Spawner = Cast<AEnemySpawner>(Actor))
		{
			EnemySpawners.Add(Spawner);
			UE_LOG(LogTemp, Warning, TEXT("Add spawner"));
		}
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandle, this, &AShootEmUpGamemode::SpawnEnemy, 3.0f, true);
	GetWorld()->GetTimerManager().PauseTimer(SpawnTimeHandle);
	CalculateEnemyCount();
}

//Spawn enemies, decrease their value count on map stop the timer when needed
void AShootEmUpGamemode::SpawnEnemy()
{

	if (EnemiesRemaining > 0)
	{
	UE_LOG(LogTemp, Warning, TEXT("Enemiesremaining > 0"));
	int RandomIndex = FMath::RandRange(0, EnemySpawners.Num() - 1);

	if (AEnemySpawner* SpawnPoint = EnemySpawners[RandomIndex])
	{

		FVector Loc = SpawnPoint->GetActorLocation();
		FRotator Rot = SpawnPoint->GetActorRotation();

		RandomEnemy = enemies[FMath::RandHelper(enemies.Num())]; // pick random item

		
		if (AEnemyCharacterBase* Enemy = GetWorld()->SpawnActor<AEnemyCharacterBase>(RandomEnemy, Loc, Rot))
		{
			--EnemiesRemaining;
		}
	}
	}
	else 
	{
		GetWorld()->GetTimerManager().PauseTimer(SpawnTimeHandle);
	}
}


//Calculate enemy count by level: Simply by: Current Level * 2
void AShootEmUpGamemode::CalculateEnemyCount()
{
	if (ShootEmUpGameState)
	{


		uint16 Level = ShootEmUpGameState->GetLevel();



		GetWorld()->GetTimerManager().UnPauseTimer(SpawnTimeHandle);
		
		// Allow new enemies by level, switch-case would be more optimal

		//Level 0-2
		if (Level <= 2)
		{
			EnemiesRemaining =	Level * 2.0f;
			UE_LOG(LogTemp, Warning, TEXT("LVL1"));
			
		}

		//Level 3-4
		else if (Level <=4)
		{
			EnemiesRemaining = Level * 3.0f;
			UE_LOG(LogTemp, Warning, TEXT("LVL3"));
			
		}

		//Level 5-6
		else if (Level > 5 && Level <= 6)
		{
			EnemiesRemaining = Level * 3.0f;
			
		}

		//Level 7-8
		else if (Level > 7 && Level <= 8)
		{
			EnemiesRemaining = Level * 3.0f;
			
		}

		//Level 9
		else if (Level == 9)
		{
			EnemiesRemaining = Level * 4.0f;
		}

		//Level 10
		else 
		{
			EnemiesRemaining = 5;
		}

		
		ShootEmUpGameState->SetTotalEnemiesRemaining(EnemiesRemaining);

	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameStateIsFalse"));
	}
}


//What to do when enemy is killed + Switch lvl
void AShootEmUpGamemode::EnemyKilled()
{
	if (ShootEmUpGameState)
	{
		ShootEmUpGameState->EnemyKilled();
		if (ShootEmUpGameState->GetTotalEnemiesRemaining() == 0)
		{	//Change Level
			
			//Used in Blueprint 
			DoAfterChangeLevel();

			ShootEmUpGameState->IncreaseLevel();
			FTimerHandle TempHandle;
			GetWorld()->GetTimerManager().SetTimer(TempHandle, this, &AShootEmUpGamemode::CalculateEnemyCount, 10.0f, false);

			PlaySwitchLevelSound();

		}
		
	}
}

//Switch lvl sound to play
void AShootEmUpGamemode::PlaySwitchLevelSound()
{
	if (SwitchLevelSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SwitchLevelSound, 0.5f, 1.0f, 0.0f);
	}

}

//getter for gamestate
AShootEmUpGameState* AShootEmUpGamemode::GetOurGameState()
{
	return ShootEmUpGameState;
}
