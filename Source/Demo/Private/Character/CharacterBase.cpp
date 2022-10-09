// Created by Tommi Kekomäki, all code free to use for educational purposes


#include "Character/CharacterBase.h"
#include "GAS/AttributeSetBase.h"
#include "Components/CapsuleComponent.h"
#include "GAS/GameplayAbilityBase.h"
#include "Math/UnrealMathUtility.h"
#include "ShootEmUpGamemode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Demo/Private/GAS/ASCBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bDeathMontagePlayed = false;

	
	AShootEmUpGamemode* GM = (AShootEmUpGamemode*)GetWorld()->GetAuthGameMode();
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Get ASC
class UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

// Charactyer level
int32 ACharacterBase::GetCharacterLevel() const
{
	//TODO
	return 1;
}

//Drop item
void ACharacterBase::DropItems()
{
	//Take random item, array has more mana actors than weapons, so weapons are more rare
	RandomItem = ItemsToDrop[FMath::RandHelper(ItemsToDrop.Num())]; // pick random item
	
	float randomNumber;
	float min = 1.0f;
	float max = 10.0f;
	randomNumber = FMath::RandRange(min, max);

	if (RandomItem)
	{
	FVector Loc = this->GetActorLocation();
	FRotator Rot = this->GetActorRotation();

	if (randomNumber <= 6)
	{
		GetWorld()->SpawnActor<AActor>(RandomItem, Loc, Rot);

	}
	}
}

//Give new ability
void ACharacterBase::AddNewAbility(TSubclassOf<UGameplayAbilityBase> NewAbility)
{

		if (HasAuthority() && NewAbility)
		{
			GetAbilitySystemComponent()->GiveAbility(
				FGameplayAbilitySpec(NewAbility, GetAbilityLevel(NewAbility.GetDefaultObject()->AbilityID), static_cast<int32>(NewAbility.GetDefaultObject()->AbilityInputID), this));
		}
}

// Check if we have asc + defaultattributes set and Initialize Attributes
void ACharacterBase::InitializeAttributes()
{
	UE_LOG(LogTemp, Warning, TEXT("initialize called"));

	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	if (!DefaultAttributes)
	{
		//UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

// Grant abilities on server
void ACharacterBase::AddCharacterAbilities()
{

	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UGameplayAbilityBase>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = true;
}

//Give new abilities to character
void ACharacterBase::AddNewAbilities(TArray<TSubclassOf<UGameplayAbilityBase>> NewAbilities)
{


	for (TSubclassOf<UGameplayAbilityBase> AbilityItem : NewAbilities)
	{
	AddNewAbility(AbilityItem);
	}

}

//Level not implemented
int32 ACharacterBase::GetAbilityLevel(EAbilityInputID AbilityID) const
{
	return 1;
}

bool ACharacterBase::IsAlive() const
{
	return GetHealth() > 0.0f;
}


//Setters
void ACharacterBase::SetHealth(float Health)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetHealth(Health);
	}
}

void ACharacterBase::SetMana(float Mana)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetMana(Mana);
	}
}
 
 //Getters
float ACharacterBase::GetHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetHealth();
	}

	return 0.0f;
}

float ACharacterBase::GetMaxHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxHealth();
	}

	return 0.0f;
}

float ACharacterBase::GetMana() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMana();
	}

	return 0.0f;
}

float ACharacterBase::GetMaxMana() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->GetMaxMana();
	}

	return 0.0f;
}

// Dying
void ACharacterBase::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("DYING"));

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAllAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);

		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
		UE_LOG(LogTemp, Warning, TEXT("DeathMontage"));
		if (OurGameMode)
		{
			/*OurGameMode->RestartOurGameTest();*/
		}
	
		FinishDying();
		
	}
	else
	{
		FinishDying();
	}
	
}

void ACharacterBase::EnemyDie()
{
	// Only runs on Server
	//RemoveCharacterAbilities();



	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	//Gamemode
	if (AShootEmUpGamemode* GM = GetWorld()->GetAuthGameMode<AShootEmUpGamemode>())
	{
		GM->EnemyKilled();
		UE_LOG(LogTemp, Warning, TEXT("DYING"));
	}


	//Abilities
	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAllAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);

		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	//Dying
	if (DeathMontage)
	{

		Tags.Remove(FName("Enemy"));
		PlayAnimMontage(DeathMontage);
		UE_LOG(LogTemp, Warning, TEXT("Montage"));

		float time;
		time = DeathMontage->GetPlayLength();


		FTimerHandle FTempHandle;
		GetWorld()->GetTimerManager().SetTimer(FTempHandle, this, &ACharacterBase::FinishDying, time - 0.5f, false);

	}

}


void ACharacterBase::FinishDying()
{
	UE_LOG(LogTemp, Warning, TEXT("DESTROY"));
	Destroy();
	DropItems();
}
