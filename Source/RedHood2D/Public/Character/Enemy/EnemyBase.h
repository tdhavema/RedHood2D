// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimationComponent.h"
#include "Character/CharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "EnemyBase.generated.h"

class UHealthBarWidget;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class REDHOOD2D_API AEnemyBase : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AEnemyBase();

	/* Implement Enemy Interface */
	virtual void SetHitReacting_Implementation(bool bHitReacting) override;

	virtual void SetCombatTarget(AActor* CombatTarget) override;
	virtual void Attack_Implementation() override;
	void InitializeOverheadHealthBar();

	UFUNCTION(BlueprintImplementableEvent)
	void K2_SetCombatTarget(AActor* CombatTarget);

protected:

	virtual void BeginPlay() override;
	virtual void GetHit(float InDamage) override;

private:

	void ChangeDirections();
	void Die();

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetComponent> HealthBarWidget;

	UPROPERTY()
	TObjectPtr<UHealthBarWidget> HealthBar;
};
