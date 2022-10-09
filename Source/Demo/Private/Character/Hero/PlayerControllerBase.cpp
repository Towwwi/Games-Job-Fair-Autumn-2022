// Created by Tommi Kekomäki, all code free to use for educational purposes
#include "Character/Hero/PlayerControllerBase.h"
#include "AbilitySystemComponent.h"
#include "Character/Hero/HeroCharacter.h"
#include "UI/DamageTextWidget.h"
#include "UI/PlayerUserWidgetBase.h"
#include "Character/Hero/PlayerStateBase.h"




void APlayerControllerBase::CreateHUD()
{

	// Only create once
	if (UIHUDWidget)
	{
		return;
	}

	if (!UIHUDWidgetClass)
	{
		//UE_LOG(LogTemp, Error, TEXT("%s() Missing UIHUDWidgetClass. Please fill in on the Blueprint of the PlayerController."), *FString(__FUNCTION__));
		return;
	}


	// Only create a HUD for local player
	if (!IsLocalPlayerController())
	{
		return;
	}

	// Need a valid PlayerState to get attributes from
	APlayerStateBase* PS = GetPlayerState<APlayerStateBase>();
	if (!PS)
	{
		return;
	}

		UIHUDWidget = CreateWidget<UPlayerUserWidgetBase>(this, UIHUDWidgetClass);
		UIHUDWidget->AddToViewport();

		UIHUDWidget->SetCurrentHealth(PS->GetHealth());
		UIHUDWidget->SetMaxHealth(PS->GetMaxHealth());
		UIHUDWidget->SetHealthPercentage(PS->GetHealth() / FMath::Max<float>(PS->GetMaxHealth(), 1.f));
		UIHUDWidget->SetCurrentMana(PS->GetMana());
		UIHUDWidget->SetMaxMana(PS->GetMaxMana());
		UIHUDWidget->SetManaPercentage(PS->GetMana() / FMath::Max<float>(PS->GetMaxMana(), 1.f));

	DamageNumberClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/Bl/UI/UI_DamageText.UI_DamageText_C"));
	if (!DamageNumberClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageNumberClass is null at playercontroller"));
		return;
	}

}

class UPlayerUserWidgetBase* APlayerControllerBase::GetHUD()
{
	return UIHUDWidget;
}

void APlayerControllerBase::ShowDamageNumber_Implementation(float DamageAmount, ACharacterBase* TargetCharacter)
{
	if (TargetCharacter)
	{
		UDamageTextWidget* DamageText = NewObject<UDamageTextWidget>(TargetCharacter, DamageNumberClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->SetDamageText(DamageAmount);

		if (DamageText == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("DamageText == nullptr"));

			return;
		}
	}
	else if (TargetCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetCharacter == nullptr"));
		return;
	}
}

bool APlayerControllerBase::ShowDamageNumber_Validate(float DamageAmount, ACharacterBase* TargetCharacter)
{
	return true;
}


UPlayerUserWidgetBase* APlayerControllerBase::AccessHud(UPlayerUserWidgetBase* CharacterHUD)
{
	if (UIHUDWidget)
	{
		CharacterHUD = GetHUD();
	}
	return CharacterHUD;
}

// Server only
void APlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	APlayerStateBase* PS = GetPlayerState<APlayerStateBase>();
	if (PS)
	{
		// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}

	CreateHUD();
}

void APlayerControllerBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For edge cases where the PlayerState is repped before the Hero is possessed.
	CreateHUD();
}
