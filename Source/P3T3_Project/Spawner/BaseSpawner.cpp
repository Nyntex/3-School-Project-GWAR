// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpawner.h"

// Sets default values for this component's properties
UBaseSpawner::UBaseSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	spawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	spawnBox->SetupAttachment(this);
	spawnBox->SetLineThickness(1.5f);
	spawnBox->ShapeColor = FColor::Cyan;
	// ...
}


// Called when the game starts
void UBaseSpawner::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UBaseSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//void UBaseSpawner::SpawnUnit()
//{
//	FVector groundSpawnPosition = FVector::Zero();
//	FindPositionInRange(groundSpawnPosition, false, true);
//
//	if(randomizeSpawnedActors)
//	{
//	    GetWorld()->SpawnActorAbsolute(GetRandomActorClass(), );
//	}
//	else
//	{
//		GetWorld()->SpawnActorAbsolute();
//		currentIndexOfActorsToSpawn++;
//	}
//}

void UBaseSpawner::Trigger(bool& spawning, bool forced)
{
	if (!isTriggerable && !forced) return;
	if (triggerOnlyOnce && triggered && !forced) return;
	triggered = !triggered;
	spawningEnabled = !spawningEnabled;
	spawning = spawningEnabled;
}

void UBaseSpawner::FindPositionInRange(FVector& position, bool local) const
{
	FVector size = spawnBox->GetScaledBoxExtent();
	FVector tempVector = GetOwner()->GetActorForwardVector() * size.X + GetOwner()->GetActorRightVector() * size.Y + GetOwner()->GetActorUpVector() * size.Z;
	FVector startPosition = GetOwner()->GetActorLocation() - tempVector;
	FVector randomPosition = 
		((rand() % int(size.X) * 2) * GetOwner()->GetActorForwardVector()) + 
		((rand() % int(size.Y) * 2) * GetOwner()->GetActorRightVector()) +
		((rand() % int(size.Z) * 2) * GetOwner()->GetActorUpVector()) + (startPosition * !local);
	position = randomPosition;
}

//void UBaseSpawner::ProjectPositionToGround(FVector& position) const
//{
//
//}

TSubclassOf<AActor> UBaseSpawner::GetRandomActorClass() const
{

	return actorsToSpawn[rand()%actorsToSpawn.Num()];
}


