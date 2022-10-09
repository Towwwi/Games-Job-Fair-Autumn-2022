// Created by Tommi Kekomäki, all code free to use for educational purposes

#include "Character/Hero/PlayerStateBase.h"
#include "GAS/AttributeSetBase.h"

APlayerStateBase::APlayerStateBase()
{

	
	ASC = CreateDefaultSubobject<UASCBase>(TEXT("ASC"));
	ASC->SetIsReplicated(true);

	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another GDPlayerState (Hero) receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	NetUpdateFrequency = 100.0f;

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	AttributeSetBase = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSetBase"));
}

//Attribute changes
void APlayerStateBase::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;
}

void APlayerStateBase::MaxHealthChanged(const FOnAttributeChangeData& Data)
{

}

void APlayerStateBase::ManaChanged(const FOnAttributeChangeData& Data)
{
	float Mana = Data.NewValue;
}

void APlayerStateBase::MaxManaChanged(const FOnAttributeChangeData& Data)
{

}








//Palauttaa meidän oman ASC:n
class UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return ASC;
}

class UAttributeSetBase* APlayerStateBase::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

float APlayerStateBase::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float APlayerStateBase::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float APlayerStateBase::GetMana() const
{
	return AttributeSetBase->GetMana();
}

float APlayerStateBase::GetMaxMana() const
{
	return AttributeSetBase->GetMaxMana();
}