// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RedHoodCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperZDAnimInstance.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/OverlayWidget.h"


ARedHoodCharacter::ARedHoodCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	// Components like the camera boom and camera are best left to adjust their settings
	// inside blueprints for ease of use and for iteration times.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bInheritYaw = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);

	PaperZDAnimComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>("AnimComponent");

}

void ARedHoodCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const APlayerController* LocalPlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(RedHoodMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARedHoodCharacter::Move);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ARedHoodCharacter::AttackButtonPressed);
		}
	}
}

void ARedHoodCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CreateOverlay();
}

void ARedHoodCharacter::Move(const FInputActionValue& Value)
{
	if (bAttacking) return;
	
	const FVector ForwardDirection = FVector(1.f, 0.f, 0.f);

	RotateController();
	
	AddMovementInput(ForwardDirection, FMath::RoundToInt(Value.GetMagnitude()));
}

void ARedHoodCharacter::RotateController() const
{
	const FVector Acceleration = GetCharacterMovement()->GetCurrentAcceleration();

	if (Acceleration.X == 0.f)
	{
		// Returning early like this means if this is the case, we don't want to do anything just stop the function.
		return;
	}

	// If it makes it to this check, then you already know it's not 0
	if (Acceleration.X > 0)
	{
		GetController()->SetControlRotation(FRotator::ZeroRotator);
	}
	else
	{
		GetController()->SetControlRotation(FRotator(0.f, -180.f, 0.f));
	}
}

void ARedHoodCharacter::AttackButtonPressed(const FInputActionValue& Value)
{
	if (IsValid(PaperZDAnimComponent))
	{
		if (bAttackWindowOpen)
		{
			bComboActivated = true;
		}
		else if (!bAttacking)
		{
			PlayFirstAttack();
		}
	}
}

void ARedHoodCharacter::Jump()
{
	if (bAttacking) return;
	
	Super::Jump();
}

void ARedHoodCharacter::CreateOverlay()
{
	if (IsValid(PlayerController))
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, OverlayWidgetClass);
		OverlayWidget = Cast<UOverlayWidget>(Widget);

		// This is so the Health Progress Bar has initial values on loading up.
		OverlayWidget->UpdateHealth(Health, MaxHealth);
		OverlayWidget->AddToViewport();
	}
}

void ARedHoodCharacter::DecrementHealth(float InDamage)
{
	Super::DecrementHealth(InDamage);

	if (IsValid(OverlayWidget))
	{
		OverlayWidget->UpdateHealth(Health, MaxHealth);
	}
}

void ARedHoodCharacter::PlayFirstAttack()
{
	bAttacking = true;
			
	if (UPaperZDAnimInstance* OwningInstance = PaperZDAnimComponent->GetAnimInstance())
	{
		PlayComboAttack(OwningInstance, 0);
	}
}

void ARedHoodCharacter::ResetAttacking_Implementation()
{
	HandleAttackReset();
}

void ARedHoodCharacter::HandleAttackReset()
{
	if (!bComboActivated)
	{
		bAttacking = false;
		AttackCount = 0;
	}
	else if (IsValid(PaperZDAnimComponent))
	{
		if (UPaperZDAnimInstance* OwningInstance = PaperZDAnimComponent->GetAnimInstance())
		{
			if (IncrementAttackCount())
			{
				bAttacking = false;
				bComboActivated = false;
				AttackCount = 0;
			}
			else
			{
				PlayComboAttack(OwningInstance, AttackCount);
				bComboActivated = false;
			}
		}
	}
}

void ARedHoodCharacter::PlayComboAttack(UPaperZDAnimInstance* OwningInstance, int32 InAttackCount)
{
	const FAttackAnimData SelectedData = AttackAnimData[InAttackCount];
	
	OwningInstance->PlayAnimationOverride(SelectedData.AttackAnimation);
	Damage = SelectedData.AttackDamage;
	TraceExtent = SelectedData.BoxTraceExtent;
	BoxTraceStart->SetRelativeLocation(SelectedData.BoxTraceStart);
	BoxTraceEnd->SetRelativeLocation(SelectedData.BoxTraceEnd);
}

bool ARedHoodCharacter::IncrementAttackCount()
{
	++AttackCount;

	return AttackCount > AttackAnimData.Num() - 1;
}

void ARedHoodCharacter::SetAttackWindowOpen_Implementation(bool bOpen)
{
	bAttackWindowOpen = bOpen;
}

void ARedHoodCharacter::ResetCombatVariables_Implementation()
{
	SetInputEnabled(true);
	bAttacking = false;
	bAttackWindowOpen = false;
	bComboActivated = false;
	AttackCount = 0;
}
