// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "RedHoodAnimInstance.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class REDHOOD2D_API URedHoodAnimInstance : public UPaperZDAnimInstance
{
	GENERATED_BODY()

public:
	void StoreEssentialVariables();
	virtual void OnInit_Implementation() override;
	void UpdateEssentialVariables();
	virtual void OnTick_Implementation(float DeltaTime) override;
private:

	UPROPERTY()
	TObjectPtr<ACharacter> OwningCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

	// All of the variables we need to change states will implement here for access

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category= "Essential Variables")
	bool bIsMoving;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category= "Essential Variables")
	bool bIsFalling;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category= "Essential Variables")
	FVector Velocity;
	
};
