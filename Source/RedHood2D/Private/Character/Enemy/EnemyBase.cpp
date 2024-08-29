// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyBase.h"

#include "PaperZDAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/HealthBarWidget.h"

AEnemyBase::AEnemyBase()
{
	GetCharacterMovement()->SetPlaneConstraintEnabled(true);
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	GetCharacterMovement()->MaxWalkSpeed = 120.f;

	PaperZDAnimComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>("AnimationComponent");

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidget");
	HealthBarWidget->SetupAttachment(GetRootComponent());
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeOverheadHealthBar();
}

void AEnemyBase::InitializeOverheadHealthBar()
{
	if (IsValid(HealthBarWidget))
	{
		HealthBar = Cast<UHealthBarWidget>(HealthBarWidget->GetWidget());

		if (IsValid(HealthBar))
		{
			HealthBar->SetProgressBarPercent(UKismetMathLibrary::SafeDivide(Health, MaxHealth));
		}
	}
}

void AEnemyBase::ChangeDirections()
{
	const FRotator TargetRotation = GetActorRotation() + FRotator(0.f, 0.f, 180.f);
	
	SetActorRotation(TargetRotation);
}

void AEnemyBase::GetHit(float InDamage)
{
	Super::GetHit(InDamage);

	if (IsValid(HealthBar))
	{
		HealthBar->SetProgressBarPercent(UKismetMathLibrary::SafeDivide(Health, MaxHealth));
	}

	if (Health <= 0.f)
	{
		Die();
	}
}

void AEnemyBase::Die()
{
	if (UBlackboardComponent* Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(GetController()))
	{
		Blackboard->SetValueAsBool(FName("bAlive"), false);
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (IsValid(HealthBar))
	{
		HealthBar->SetVisibility(ESlateVisibility::Hidden);
	}

	bAlive = false;

	SetActorTickEnabled(false);

	if (IsValid(PaperZDAnimComponent))
	{
		if (UPaperZDAnimInstance* OwningInstance = PaperZDAnimComponent->GetAnimInstance())
		{
			OwningInstance->StopAllAnimationOverrides();
		}
	}
}

void AEnemyBase::SetHitReacting_Implementation(bool bHitReacting)
{
	if (UBlackboardComponent* Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(GetController()))
	{
		Blackboard->SetValueAsBool(FName("bHitReacting"), bHitReacting);
	}
}

void AEnemyBase::SetCombatTarget(AActor* CombatTarget)
{
	
}

void AEnemyBase::Attack_Implementation()
{
	
}
