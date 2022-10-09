// Created by Tommi Kekomäki, all code free to use for educational purposes
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * This class has some function's by Tranek's GAS Documentation. I always use these as a GAS-base functions for projects that use Gameplay Ability System -plugin and adjust them a little to my needs.
 * https://github.com/tranek/GASDocumentation
 *    I'm not sure what are Tranek's functions and what are functions created by me years ago i started experimenting with gas.
 */
UCLASS()
class APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:

	void CreateHUD();

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UDamageTextWidget> DamageNumberClass;

	
	class UPlayerUserWidgetBase* GetHUD();

	UFUNCTION(Client, Reliable, WithValidation)
	void ShowDamageNumber(float DamageAmount, ACharacterBase* TargetCharacter);
	void ShowDamageNumber_Implementation(float DamageAmount, ACharacterBase* TargetCharacter);
	bool ShowDamageNumber_Validate(float DamageAmount, ACharacterBase* TargetCharacter);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
		TSubclassOf<class UPlayerUserWidgetBase> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
		class UPlayerUserWidgetBase* UIHUDWidget;

	UFUNCTION(BlueprintCallable)
	virtual UPlayerUserWidgetBase* AccessHud(UPlayerUserWidgetBase* CharacterHUD);

	// Server only
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;
};
