// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = maxHealth;
	startPosition = GetActorLocation();
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::ReduceHealth(float Amount, bool& aboveZero)
{
	currentHealth -= Amount;
	aboveZero = currentHealth > 0;
	//return AboveZero;
}

void AEnemyBase::IncreaseHealth(float amount, bool clampToMax)
{
	currentHealth += amount;
	if(currentHealth > maxHealth && clampToMax)
	{
		currentHealth = maxHealth;
	}
}

void AEnemyBase::GetClosestActor(const TArray<AActor*>& actors, AActor*& closestActor) const
{
	closestActor = actors[0];
	float closestDistance = GetDistanceTo(closestActor);

	for(AActor* guy : actors)
	{
		float nextDistance = GetDistanceTo(guy);
		if(nextDistance < closestDistance)
		{
			closestActor = guy;
			closestDistance = nextDistance;
		}
	}
}

void AEnemyBase::IsActorInAttackRange(AActor* target, float& distance, bool& inRange) const
{
	distance = GetDistanceTo(target);
	inRange = distance <= attackRange;
}

void AEnemyBase::GetDegreeToTarget(AActor* fromTarget, AActor* toTarget, float& degree, float& radians) const
{
	FVector forward = fromTarget->GetActorForwardVector();
	FVector direction = toTarget->GetActorLocation() - fromTarget->GetActorLocation();
	direction.Normalize();

	radians = acos((forward.X * direction.X + forward.Y * direction.Y + forward.Z * direction.Z) / 
		(sqrt(pow(forward.X, 2) + pow(forward.Y, 2) + pow(forward.Z,2)) * 
			sqrt(pow(direction.X, 2) + pow(direction.Y, 2) + pow(direction.Z, 2))));

	degree = (radians * 180) / UE_PI;
}

void AEnemyBase::ChangeState(EEnemyStates newState, EEnemyStates& state)
{
	currentState = newState;
	state = newState;
}

