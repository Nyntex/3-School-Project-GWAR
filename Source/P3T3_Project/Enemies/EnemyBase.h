// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UENUM(BlueprintType)
enum class EEnemyStates : uint8
{
	Invalid = 0,
	IDLE = 1,
	FLEE = 5,
	CHASE = 10,
};

UCLASS()
class P3T3_PROJECT_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ChangeState(EEnemyStates newState, EEnemyStates& state);

	/**Automatically assigns and returns the new Health value as well as returning if the value is zero or not */
	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float amount, bool& aboveZero);

	/**Automatically assigns and returns the new Health value as well as clamping it to the max health value */
	UFUNCTION(BlueprintCallable)
	void IncreaseHealth(float amount, bool clampToMax = true);

	UFUNCTION(BlueprintCallable)
	void GetClosestActor(const TArray<AActor*>& actors, AActor*& closestActor) const;

	UFUNCTION(BlueprintCallable)
	void IsActorInAttackRange(AActor* target, float& distance, bool& inRange) const;

	/**Get the angle of the looking direction of the fromTarget to the toTarget */
	UFUNCTION(BlueprintCallable)
	void GetDegreeToTarget(AActor* fromTarget, AActor* toTarget, float& degree, float& radians) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	//Member
protected:
	//DefaultOnly Values
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float maxHealth = 1.0f;
	UPROPERTY(BlueprintReadWrite)
	float currentHealth = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float baseDamage = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float attackRange = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float attacksPerSecond = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float reactionTime = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float looseAggroTime = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float movementSpeed = 300.0f;

	//Anywhere values
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	FVector startPosition = FVector(0,0,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxDistanceToWanderOfIdle = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> targetables;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AActor*> targetableActors;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EEnemyStates currentState = EEnemyStates::IDLE;
};
