// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Enemy_Skeleton.h"

void AEnemy_Skeleton::SetCombatTarget(AActor* CombatTarget)
{
	K2_SetCombatTarget(CombatTarget);
}

void AEnemy_Skeleton::Attack_Implementation()
{
	K2_Attack();
}
