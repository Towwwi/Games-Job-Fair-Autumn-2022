// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "ProjectileBase.generated.h"

UCLASS()
class AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values
	AProjectileBase();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true))
	float Range;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileMovement;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particles");
	UParticleSystem* ProjectileParticles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
