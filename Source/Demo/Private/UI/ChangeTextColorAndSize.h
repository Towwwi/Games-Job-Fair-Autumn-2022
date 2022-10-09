// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * To change dmg number color
 */
class ChangeTextColorAndSize
{
public:
	ChangeTextColorAndSize();
	


	UFUNCTION(BlueprintReadWrite, VisibleAnywhere, meta = (DeprecatedFunction))
	bool ChangeTextColor(const FString& InString);

};
