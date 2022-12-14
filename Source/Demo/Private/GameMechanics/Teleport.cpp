// Created by Tommi Kekomäki, all code free to use for educational purposes

#include "GameMechanics/Teleport.h"
#include "Character/Hero/HeroCharacter.h"


ATeleport::ATeleport()
{
	bTeleportUsed = false;

	OnActorBeginOverlap.AddDynamic(this, &ATeleport::TeleportEnter);
	OnActorBeginOverlap.AddDynamic(this, &ATeleport::TeleportExit);
}


//character overlap teleport trigger
void ATeleport::TeleportEnter(class AActor* overlappedActor, class AActor* otherActor)
{
	 	if (TeleporterToTele)
		{
			AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(otherActor);
			if (HeroCharacter && !TeleporterToTele->bTeleportUsed)
 			{
				bTeleportUsed = true;
				HeroCharacter->SetActorRotation(TeleporterToTele->GetActorRotation());
				HeroCharacter->GetController()->SetControlRotation(HeroCharacter->GetActorRotation());
				HeroCharacter->SetActorLocation(TeleporterToTele->GetActorLocation());
	 		}
		}
}

void ATeleport::TeleportExit(class AActor* overlappedActor, class AActor* otherActor)
{
	if (TeleporterToTele && bTeleportUsed)
	{
	TeleporterToTele->bTeleportUsed = false;
	}
}
