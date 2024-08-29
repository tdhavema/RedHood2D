// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Animation/EnemyAnimInstanceBase.h"

#include "Character/Enemy/EnemyBase.h"

void UEnemyAnimInstanceBase::OnInit_Implementation()
{
	StoreEssentialVariables();
}

void UEnemyAnimInstanceBase::OnTick_Implementation(float DeltaTime)
{
	if (!IsValid(EnemyBase))
	{
		StoreEssentialVariables();
	}

	if (!IsValid(EnemyBase)) return;

	bIsMoving = EnemyBase->GetVelocity().Size() > 0.f;
	
}

void UEnemyAnimInstanceBase::StoreEssentialVariables()
{
	EnemyBase = Cast<AEnemyBase>(GetOwningActor());
}

