// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperZDAnimationComponent.h"
#include "Interface/EnemyInterface.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class REDHOOD2D_API AEnemyBase : public APaperCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AEnemyBase();

	virtual void SetCombatTarget(AActor* CombatTarget) override;
	virtual void Attack_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent)
	void K2_SetCombatTarget(AActor* CombatTarget);

	UFUNCTION(BlueprintImplementableEvent)
	void K2_Attack();

private:

	void ChangeDirections();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UPaperZDAnimationComponent> PaperZDAnimComponent;
	
};
