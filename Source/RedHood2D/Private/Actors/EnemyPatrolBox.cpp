// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemyPatrolBox.h"

#include "Character/Enemy/EnemyBase.h"
#include "Components/BoxComponent.h"
#include "Interface/PlayerInterface.h"


AEnemyPatrolBox::AEnemyPatrolBox()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");

}

void AEnemyPatrolBox::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AEnemyPatrolBox::OnBoxBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AEnemyPatrolBox::OnBoxEndOverlap);
}

void AEnemyPatrolBox::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UPlayerInterface>())
	{
		for (AEnemyBase* Actor : PatrolActors)
		{
			if (IEnemyInterface* Interface = Cast<IEnemyInterface>(Actor))
			{
				Interface->SetCombatTarget(OtherActor);
			}
		}
	}
}

void AEnemyPatrolBox::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UPlayerInterface>())
	{
		for (AEnemyBase* Actor : PatrolActors)
		{
			if (IEnemyInterface* Interface = Cast<IEnemyInterface>(Actor))
			{
				Interface->SetCombatTarget(nullptr);
			}
		}
	}
}

