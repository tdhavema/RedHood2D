// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PaperCharacter.h"
#include "Interface/PlayerInterface.h"
#include "RedHoodCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class REDHOOD2D_API ARedHoodCharacter : public APaperCharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	
	ARedHoodCharacter();

protected:

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

private:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category="Custom Values|Input")
	TObjectPtr<UInputMappingContext> RedHoodMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Custom Values|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category= "Custom Values|Input")
	TObjectPtr<UInputAction> JumpAction;

	void RotateController() const;
	

};
