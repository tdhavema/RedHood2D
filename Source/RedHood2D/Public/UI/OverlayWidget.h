// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class REDHOOD2D_API UOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateHealth(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent)
	void K2_UpdateHealth(float CurrentHealth, float MaxHealth);
	
};
