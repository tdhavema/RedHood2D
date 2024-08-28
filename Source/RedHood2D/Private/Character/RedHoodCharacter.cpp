// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RedHoodCharacter.h"

// Sets default values
ARedHoodCharacter::ARedHoodCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARedHoodCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARedHoodCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARedHoodCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

