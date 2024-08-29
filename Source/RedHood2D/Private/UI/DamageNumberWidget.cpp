// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageNumberWidget.h"

void UDamageNumberWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartSelfDestructDelay();
}

void UDamageNumberWidget::StartSelfDestructDelay()
{
	GetWorld()->GetTimerManager().SetTimer(SelfDestructTimerHandle, this, &UDamageNumberWidget::SelfDestructDelayFinished, 1.f);
}

void UDamageNumberWidget::SelfDestructDelayFinished()
{
	RemoveFromParent();
}
