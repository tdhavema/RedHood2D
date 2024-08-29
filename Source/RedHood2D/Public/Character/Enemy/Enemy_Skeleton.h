// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/EnemyBase.h"
#include "Enemy_Skeleton.generated.h"

/**
 * 
 */
UCLASS()
class REDHOOD2D_API AEnemy_Skeleton : public AEnemyBase
{
	GENERATED_BODY()

public:

	/* Implement Enemy Interface */
	virtual void SetCombatTarget(AActor* CombatTarget) override;
	virtual void Attack_Implementation() override; 
	
};
