// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RedHoodCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


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

}


void ARedHoodCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARedHoodCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARedHoodCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(RedHoodMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARedHoodCharacter::Move);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		}
	}
}

void ARedHoodCharacter::Move(const FInputActionValue& Value)
{
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

