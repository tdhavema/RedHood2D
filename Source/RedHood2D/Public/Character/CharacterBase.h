// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperZDAnimationComponent.h"
#include "CharacterBase.generated.h"

class UNiagaraSystem;
class UPaperZDAnimSequence;
/**
 * 
 */
UCLASS()
class REDHOOD2D_API ACharacterBase : public APaperCharacter
{
	GENERATED_BODY()

public:

	ACharacterBase();

	UFUNCTION(BlueprintImplementableEvent)
	void K2_HandleAttackHit(const FHitResult& HitResult);
	
	UFUNCTION(BlueprintImplementableEvent)
	void K2_InterfaceAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void K2_CreateDamageNumber(float Number, const FSlateColor& ColorAndOpacity);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bAlive = true;

protected:

	virtual void BeginPlay() override;
	virtual void DecrementHealth(float InDamage); 

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UFUNCTION(BlueprintCallable)
	void AttackBoxTrace();

	UFUNCTION(BlueprintCallable)
	void PlayAttackAnim();

	UFUNCTION(BlueprintCallable)
	void PlayAnimBasedOnHealth();

	UFUNCTION(BlueprintCallable)
	virtual void GetHit(float InDamage);

	UFUNCTION(BlueprintCallable)
	void SetInputEnabled(bool bEnabled);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UPaperZDAnimationComponent> PaperZDAnimComponent;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category= "Combat")
	float Health = 100.f;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category= "Combat")
	float MaxHealth = 100.f;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category= "Combat")
	float Damage = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> BoxTraceStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> BoxTraceEnd;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category= "Custom Values|Attack Trace")
	FVector TraceExtent;

	

private:
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category= "Custom Values|Attack Trace")
	FRotator BoxRotation;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category= "Custom Values|Attack Trace")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category= "Custom Values|Attack Trace")
	TObjectPtr<UPaperZDAnimSequence> AttackAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category= "Hit React")
	TObjectPtr<UPaperZDAnimSequence> HitReactAnimation;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category= "Hit React")
	TObjectPtr<UNiagaraSystem> HitReactParticles;

	UPROPERTY(EditDefaultsOnly, Category= "Custom Values|Damage Number")
	FSlateColor DamageNumberSlate;

	UPROPERTY(EditDefaultsOnly, Category="Custom Values|Damage Number")
	TSubclassOf<UUserWidget> DamageNumberWidgetClass;

	void CreateDamageNumber(float Number, const FVector& Location);
	void SpawnHitEffects(); 
};
