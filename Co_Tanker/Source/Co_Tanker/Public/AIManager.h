// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIManager.generated.h"

class ATank;

/**
* This class is in charge of spawn, delete AI tanks in each round.
*/
UCLASS()
class CO_TANKER_API AAIManager : public AActor
{
	GENERATED_BODY()
	
private:
	// This should be done in BeginPlay;
	TArray<AActor*> SpawnPoints;

	// Both body and turret will be syc health.
	TArray<AActor*> PlayerTanks;

	TArray<AActor*> AITanks;

	UPROPERTY(EditAnywhere, Category = RoundManager)
	float RoundInterval = 0;

	UPROPERTY(VisibleAnywhere, Category = RoundManager)
	float NextRoundStartTime = 0;

	UPROPERTY(EditAnywhere, Category = RoundManager)
	int32 TankLeft = 0;

	UPROPERTY(VisibleAnywhere, Category = RoundManager)
	int32 Round = 1;

	UPROPERTY(VisibleAnywhere, Category = RoundManager)
	int32 TankToSpawn = Round;

	UPROPERTY(EditAnywhere, Category = RoundManager)
	TSubclassOf<ATank> AITank_BP;

	UPROPERTY(VisibleAnywhere, Category = RoundManager)
	float SpawnTime = 5.0f;

	UPROPERTY(EditAnywhere, Category = RoundManager)
	float SpawnIntervalDefault = 5.0f;

	void SpawnAnAITank();

	void StartNewRound();

	UFUNCTION()
	void OnAITankDestroy();

public:	
	// Sets default values for this actor's properties
	AAIManager();

	UFUNCTION(BlueprintPure, Category = RoundManager)
	int GetRound() { return Round; }

	UFUNCTION(BlueprintPure, Category = RoundManager)
	int GetTankLeft() { return TankLeft; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
