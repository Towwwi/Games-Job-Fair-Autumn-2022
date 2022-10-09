// Created by Tommi Kekomäki, all code free to use for educational purposes


#include "GAS/ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"

// just default values and attributes to be used on BP
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
}


void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

