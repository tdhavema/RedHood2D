// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyBase.h"

#include "GameFramework/CharacterMovementComponent.h"

AEnemyBase::AEnemyBase()
{
	GetCharacterMovement()->SetPlaneConstraintEnabled(true);
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	GetCharacterMovement()->MaxWalkSpeed = 120.f;

	PaperZDAnimComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>("AnimationComponent");
}

void AEnemyBase::SetCombatTarget(AActor* CombatTarget)
{
	
}

void AEnemyBase::Attack_Implementation()
{
	
}

void AEnemyBase::ChangeDirections()
{
	const FRotator TargetRotation = GetActorRotation() + FRotator(0.f, 0.f, 180.f);
	
	SetActorRotation(TargetRotation);
}
