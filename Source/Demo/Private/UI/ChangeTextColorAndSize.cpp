// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChangeTextColorAndSize.h"
#include "Blueprint/UserWidget.h"

ChangeTextColorAndSize::ChangeTextColorAndSize()
{
	
}

bool ChangeTextColorAndSize::ChangeTextColor(const FString& InString)
{

	float DamageNumber = FCString::Atof(*InString);

	if (DamageNumber >= 100)
	{
		return true;
	}

	return false;
}
