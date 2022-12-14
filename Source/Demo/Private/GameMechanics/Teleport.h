// Created by Tommi Kekomäki, all code free to use for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Teleport.generated.h"

/**
 * 
 */
UCLASS()
class ATeleport : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	ATeleport();

	UPROPERTY(EditAnywhere)
	bool bTeleportUsed;
	
	UPROPERTY(EditAnywhere)
	class ATeleport* TeleporterToTele;



protected:
 	
 	UFUNCTION()
 	virtual void TeleportEnter(class AActor* overlappedActor, class AActor* otherActor);
 
 	UFUNCTION()
 	virtual void TeleportExit(class AActor* overlappedActor, class AActor* otherActor);

};
