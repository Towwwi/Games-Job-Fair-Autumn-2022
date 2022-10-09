// Created by Tommi Kekomäki, all code free to use for educational purposes


#include "Character/Enemy/EnemyCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "GAS/AttributeSetBase.h"
#include "UI/EnemyBar.h"
#include "GameplayEffectTypes.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/ASCBase.h"



//Constructor, create objects and set starting values, apply ASC
AEnemyCharacterBase::AEnemyCharacterBase()
{
	// Create ability system component, and set it to be explicitly replicated
	HardRefAbilitySystemComponent = CreateDefaultSubobject<UASCBase>(TEXT("ASC"));
	HardRefAbilitySystemComponent->SetIsReplicated(true);

	// Minimal Mode means that no GameplayEffects will replicate. They will only live on the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	HardRefAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	// Set our parent's TWeakObjectPtr
	AbilitySystemComponent = HardRefAbilitySystemComponent;

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	HardRefAttributeSetBase = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSet"));


	this->Tags.Add(FName("Enemy"));

	// Set our parent's TWeakObjectPtr
	AttributeSetBase = HardRefAttributeSetBase;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);


	EnemyBarComponent = CreateDefaultSubobject<UWidgetComponent>(FName("EnemyBarComponent"));
	EnemyBarComponent->SetupAttachment(RootComponent);
	EnemyBarComponent->SetRelativeLocation(FVector(0, 0, 120));
	EnemyBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	EnemyBarComponent->SetDrawSize(FVector2D(500, 500));



	//Collisions
	bHasCollisionSocketR = false;
	bHasCollisionSocketL = false;

	EnemyBarClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/Bl/UI/UI_EnemyBar.UI_EnemyBar_C"));
	if (!EnemyBarClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Failed to find Enemybar. If it was moved, please update the reference location in C++."), *FString(__FUNCTION__));
	}

	HandHitBoxR = CreateDefaultSubobject<UBoxComponent>(TEXT("CombatCollisionR"));
	HandHitBoxL = CreateDefaultSubobject<UBoxComponent>(TEXT("CombatCollisionL"));
	bIsAttacking = false;
}

//Add attributes and abilities, choosen in Blueprint, set health and setup BarWidget
void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();


	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttributes();
		AddCharacterAbilities();

		SetHealth(GetMaxHealth());

		// Setup FloatingStatusBar UI for Locally Owned Players only, not AI or the server's copy of the PlayerControllers
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC && PC->IsLocalPlayerController())
		{
			if (EnemyBarClass)
			{
				EnemyBar = CreateWidget<UEnemyBar>(PC, EnemyBarClass);
				if (EnemyBar && EnemyBarComponent)
				{
					EnemyBarComponent->SetWidget(EnemyBar);

					// Setup the floating status bar
					EnemyBar->SetHealthPercentage(GetHealth() / GetMaxHealth());

					EnemyBar->SetCharacterName(CharacterName);
				}
			}
		}

		// Attribute change callbacks
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AEnemyCharacterBase::HealthChanged);

		// Tag change callbacks
		//AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AEnemyCharacterBase::StunTagChanged);
	
	}
}


//What happens when Health Changes
void AEnemyCharacterBase::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	// Update floating status bar
	if (EnemyBar)
	{
		EnemyBar->SetHealthPercentage(Health / GetMaxHealth());
	}

	// Death
	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		EnemyDie();
	}
}


// Activate and disable collisions
void AEnemyCharacterBase::ActivateCollisionR()
{
	HandHitBoxR->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // to only generate overlap events

}
void AEnemyCharacterBase::DeActivateCollisionR()
{

	HandHitBoxR->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void AEnemyCharacterBase::ActivateCollisionL()
{
	HandHitBoxL->SetCollisionEnabled(ECollisionEnabled::QueryOnly); 

}
void AEnemyCharacterBase::DeActivateCollisionL()
{

	HandHitBoxL->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


//Called from BP_EnemyBase -Blueprint or call in contructor when creating subobject.
void AEnemyCharacterBase::AttachCollisionR()
{

	if (bHasCollisionSocketR == true)
	{

		HandHitBoxR->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("CollisionSocketR")); // attach to spesific location on mesh
	}

}
void AEnemyCharacterBase::AttachCollisionL()
{

	if (bHasCollisionSocketL == true)
	{
		HandHitBoxL->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("CollisionSocketL")); // attach to spesific location on mesh

	}

}

