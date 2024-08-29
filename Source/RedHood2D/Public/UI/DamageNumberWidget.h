// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageNumberWidget.generated.h"

/**
 * 
 */
UCLASS()
class REDHOOD2D_API UDamageNumberWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent)
	void K2_SetNumber(float Number, const FSlateColor& NumberColorAndOpacity);

	UFUNCTION(BlueprintImplementableEvent)
	void K2_PlayAnimation();

private:

	FTimerHandle SelfDestructTimerHandle;
	void StartSelfDestructDelay();
	void SelfDestructDelayFinished();
	
};
