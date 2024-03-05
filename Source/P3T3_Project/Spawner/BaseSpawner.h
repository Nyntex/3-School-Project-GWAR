// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "BaseSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3T3_PROJECT_API UBaseSpawner : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Forcing the trigger allows to trigger untriggerable spawner making them stop spawning
	UFUNCTION(BlueprintCallable)
	virtual void Trigger(bool& spawning, bool forced = false);

	//Finds a position in the scaled box making this
	//a Three-Dimensional Spawner
	//Allows to receive the position in world or local space
	UFUNCTION(BlueprintCallable)
	void FindPositionInRange(FVector& position, bool local = false) const;

	//Picks a random actor from the given actors to spawn list
	UFUNCTION(BlueprintCallable)
	TSubclassOf<AActor> GetRandomActorClass() const;

	//Member Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	UBoxComponent* spawnBox;

	//This is only to show some more variables in the Editor's Details Panel
	UPROPERTY(EditInstanceOnly, Category = "Spawner")
	bool showDebugSettings = false;

	/** The Time it takes for the spawner to make a new spawn call */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float timeBetweenSpawns = 1.0f;

	/** The amount of units this spawner should spawn,
	 * depending on if the amount is total or current the spawner
	 * will either spawn this amount of units with the set delay
	 * or keep this amount of units in the level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	int maxUnitsToSpawn = 4;

	/** Should the spawner only spawn the total number or should it try to keep
	 * the max amount in the level*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	bool maxUnitsIsTotal = false;

	/** The amount of Actors to spawn per spawn cycle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	int amountToSpawn = 1;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Spawner", meta = (EditCondition = "showDebugSettings==true", EditConditionHides))
	int amountSpawned = 0;

	/** Actors spawned by this spawner */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Spawner", meta = (EditCondition = "showDebugSettings==true", EditConditionHides))
	TArray<AActor*> spawnedActors = TArray<AActor*>();

	/** The Classes of actors this spawner should spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TArray<TSubclassOf<AActor>> actorsToSpawn = TArray<TSubclassOf<AActor>>();

	/** If the actors that get spawned should be random
	 * or in order of the Actors to Spawn Array */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	bool randomizeSpawnedActors = true;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Spawner", meta = (EditCondition = "showDebugSettings==true", EditConditionHides))
	int currentIndexOfActorsToSpawn = 0;

	/** Should the actors spawned by this spawner spawn on the ground or in the air */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	bool spawnOnGround = true;

	/** If this Spawner should be able to get triggered */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	bool isTriggerable = true;

	/** Should the spawner start spawning as soon as the game starts */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	bool activeOnStart = true;

	/** If this trigger should only get triggered once */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	bool triggerOnlyOnce = true;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Spawner", meta = (EditCondition = "showDebugSettings==true", EditConditionHides))
	bool triggered = false;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Spawner", meta = (EditCondition = "showDebugSettings==true", EditConditionHides))
	bool spawningEnabled = false;
};
