// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "EnemyAnimInstanceBase.generated.h"

class AEnemyBase;
/**
 * 
 */
UCLASS()
class REDHOOD2D_API UEnemyAnimInstanceBase : public UPaperZDAnimInstance
{
	GENERATED_BODY()

public:
	void StoreEssentialVariables();
	virtual void OnInit_Implementation() override;
	virtual void OnTick_Implementation(float DeltaTime) override;

private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category="Character")
	TObjectPtr<AEnemyBase> EnemyBase;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category="Character")
	bool bIsMoving;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category= "Essential Variables")
	bool bIsAlive = true;
	
};
