// Created by Tommi Kekomäki, all code free to use for educational purposes


#include "Animations/AnimInstanceBase.h"
#include "Character/Hero/HeroCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gameframework/CharacterMovementComponent.h"

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Character = Cast<AHeroCharacter>(TryGetPawnOwner());
}

void UAnimInstanceBase::UpdateAnimationproperties(float DeltaTime)
{
	if (Character == nullptr)
	{
		Character = Cast<AHeroCharacter>(TryGetPawnOwner());
	}

	if (Character)
	{
		// Get speed from velocity
		FVector Velocity{ Character->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();


		//Is in Air?
		bIsInAir = Character->GetCharacterMovement()->IsFalling();

		// Is moving?
		if (Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0)
		{
			bIsAccelerating = true;
		}
		else 
		{
			bIsAccelerating = false;
		}

// 		FRotator AimRotation = Character->GetBaseAimRotation();
// 		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Character->GetVelocity());
// 
// 		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
// 
// 		FString RotationMessage = FString::Printf(TEXT("Bse Ao, Rotation: %f"), AimRotation.Yaw);

// 		if (GEngine)
// 		{
// 			GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, RotationMessage);
// 		}

	}
}
