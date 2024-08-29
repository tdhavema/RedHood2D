// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonTypes.generated.h"

class UPaperZDAnimSequence;

USTRUCT(BlueprintType)
struct FAttackAnimData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPaperZDAnimSequence> AttackAnimation = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackDamage = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector BoxTraceStart = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector BoxTraceEnd = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector BoxTraceExtent = FVector::ZeroVector;
};

