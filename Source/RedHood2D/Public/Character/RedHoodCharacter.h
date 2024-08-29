// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CommonTypes.h"
#include "InputActionValue.h"
#include "Interface/PlayerInterface.h"
#include "RedHoodCharacter.generated.h"

class UOverlayWidget;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class REDHOOD2D_API ARedHoodCharacter : public ACharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	
	ARedHoodCharacter();

	/* Implement Player Interface */
	virtual void ResetAttacking_Implementation() override;
	virtual void SetAttackWindowOpen_Implementation(bool bOpen) override;
	virtual void ResetCombatVariables_Implementation() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void AttackButtonPressed(const FInputActionValue& Value);

protected:

	virtual void BeginPlay() override;
	virtual void Jump() override;
	
	void CreateOverlay();

	virtual void DecrementHealth(float InDamage) override;
	void HandleAttackReset();

	void PlayComboAttack(UPaperZDAnimInstance* OwningInstance, int32 InAttackCount);

	bool IncrementAttackCount(); 

private:

	void RotateController() const;
	void PlayFirstAttack();

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
	
	UPROPERTY(EditDefaultsOnly, Category= "Custom Values|Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY()
	TObjectPtr<UOverlayWidget> OverlayWidget;

	UPROPERTY(EditDefaultsOnly, Category="Custom Values|UI")
	TSubclassOf<UUserWidget> OverlayWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category="Combat")
	bool bAttacking = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category="Combat")
	bool bAttackWindowOpen = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category="Combat")
	bool bComboActivated = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category="Combat")
	int32 AttackCount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category="Combat")
	TArray<FAttackAnimData> AttackAnimData;
};
