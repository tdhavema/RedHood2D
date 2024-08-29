// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "NiagaraFunctionLibrary.h"
#include "PaperZDAnimInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/DamageNumberWidget.h"

ACharacterBase::ACharacterBase()
{
	BoxTraceStart = CreateDefaultSubobject<USceneComponent>("BoxTraceStart");
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>("BoxTraceEnd");
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
}

void ACharacterBase::AttackBoxTrace()
{
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	FHitResult HitResult;

	UKismetSystemLibrary::BoxTraceSingleForObjects(this,
		BoxTraceStart->GetComponentLocation(),
		BoxTraceEnd->GetComponentLocation(),
		TraceExtent,
		BoxRotation,
		ObjectTypes,
		false,
		IgnoreActors,
		EDrawDebugTrace::None,
		HitResult,
		true);

	K2_HandleAttackHit(HitResult);
}

void ACharacterBase::PlayAttackAnim()
{
	if (UPaperZDAnimInstance* OwningInstance = PaperZDAnimComponent->GetAnimInstance())
	{
		OwningInstance->PlayAnimationOverride(AttackAnimation);
	}
}

void ACharacterBase::GetHit(float InDamage)
{
	DecrementHealth(InDamage);
	PlayAnimBasedOnHealth();
	SetInputEnabled(false);
	SpawnHitEffects();
	CreateDamageNumber(InDamage, GetActorLocation());
}

void ACharacterBase::PlayAnimBasedOnHealth()
{
	if (UPaperZDAnimInstance* OwningInstance = PaperZDAnimComponent->GetAnimInstance())
	{
		if (Health > 0.f)
		{
			OwningInstance->PlayAnimationOverride(HitReactAnimation);
		}
		else
		{
			bAlive = false;
		}
	}
}

void ACharacterBase::SetInputEnabled(bool bEnabled)
{
	if (IsValid(PlayerController))
	{
		if (bEnabled)
		{
			PlayerController->EnableInput(PlayerController);
		}
		
		if (!bEnabled)
		{
			PlayerController->DisableInput(PlayerController);
		}
	}
}

void ACharacterBase::CreateDamageNumber(float Number, const FVector& Location)
{
	if (UUserWidget* NumberWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(this, 0), DamageNumberWidgetClass))
	{
		NumberWidget->AddToViewport();
		
		if (UDamageNumberWidget* DamageNumber = Cast<UDamageNumberWidget>(NumberWidget))
		{
			DamageNumber->K2_SetNumber(Number, DamageNumberSlate);

			const FVector TargetPosition = Location + FVector(0.f, 0.f, 75.f);
			
			FVector2D ScreenLocation;
			UGameplayStatics::GetPlayerController(this, 0)->ProjectWorldLocationToScreen(TargetPosition,ScreenLocation);
			DamageNumber->SetPositionInViewport(ScreenLocation);
			DamageNumber->K2_PlayAnimation();
		}
	}
}

void ACharacterBase::SpawnHitEffects()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitReactParticles, GetActorLocation());
}

void ACharacterBase::DecrementHealth(float InDamage)
{
	Health = FMath::Clamp(Health - InDamage, 0.f, MaxHealth);
}


