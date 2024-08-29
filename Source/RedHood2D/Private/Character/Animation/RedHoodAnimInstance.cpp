// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/RedHoodAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void URedHoodAnimInstance::OnInit_Implementation()
{
	StoreEssentialVariables();
}

void URedHoodAnimInstance::StoreEssentialVariables()
{
	OwningCharacter = Cast<ACharacter>(GetOwningActor());
	CharacterMovementComponent = OwningCharacter->GetCharacterMovement();
}

void URedHoodAnimInstance::OnTick_Implementation(float DeltaTime)
{
	// If either of the essential variables aren't valid by now, what we do is just repeat the same process
	if (!IsValid(OwningCharacter) || !IsValid(CharacterMovementComponent))
	{
		StoreEssentialVariables();
	}

	// If either of the essential variables still aren't valid at this point, then just return early stop the function.
	if (!IsValid(OwningCharacter) || !IsValid(CharacterMovementComponent)) return;

	UpdateEssentialVariables();
}

void URedHoodAnimInstance::UpdateEssentialVariables()
{
	Velocity = OwningCharacter->GetVelocity();
	bIsMoving = Velocity.Size() > 0.f;

	bIsFalling = CharacterMovementComponent->IsFalling();
}
