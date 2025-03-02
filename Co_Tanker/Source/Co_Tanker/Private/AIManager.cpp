// ©Eadmond's work. All rights reserved!

#include "AIManager.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void AAIManager::SpawnAnAITank()
{
	int32 index = FMath::RandRange(0, SpawnPoints.Num() - 1);
	//UE_LOG(LogTemp, Warning, TEXT("index  %d"), index);
	AActor* spawnTransActor = SpawnPoints[index];

	auto world = GetWorld();
	if (spawnTransActor && world)
	{
		ATank* atank = world->SpawnActor<ATank>(AITank_BP, spawnTransActor->GetActorLocation(), spawnTransActor->GetActorRotation());
		atank->OnDeath.AddUniqueDynamic(this, &AAIManager::OnAITankDestroy);
		atank->SpawnDefaultController();
		AITanks.AddUnique(atank);
	}

}

void AAIManager::StartNewRound()
{
	// Increase round number
	Round++;
	
	// Set tank left for new rounds
	TankLeft = Round;
	TankToSpawn = Round;

	// Restore player health.
	for (int32 i = 0; i < PlayerTanks.Num(); i++)
	{
		// TODO need to check if the turret health need to be sync too.
		ATank* aTankBody = Cast<ATank>(PlayerTanks[i]);
		if (aTankBody)
		{
			aTankBody->SetHealth(aTankBody->GetStartHealth());
		}
	}

	// TODO Remove ai tank ramians
	for (int32 i = 0; i < AITanks.Num(); i++)
	{
		AITanks[i]->Destroy();
	}
	AITanks.Empty();

	// Start Round count down
	NextRoundStartTime = GetWorld()->GetTimeSeconds() + RoundInterval;
}

// Sets default values
AAIManager::AAIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAIManager::OnAITankDestroy()
{
	//UE_LOG(LogTemp, Warning, TEXT("An AI tank was destroyed!!"));

	TankLeft--;

	if (TankLeft <= 0)
	{
		// finish end of the wave and start next wave.
		StartNewRound();
	}

}

// Called when the game starts or when spawned
void AAIManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Get SpawnPoint from the World
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("AITankSpawnPoint"), SpawnPoints);

	// GetPlayerTankBodies
	//UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PlayerTankBody"), PlayerTanks);
	TArray<AActor*> allTanks;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATank::StaticClass(), allTanks);

	SpawnTime = SpawnIntervalDefault + GetWorld()->GetTimeSeconds();

	for (int32 i = 0; i < allTanks.Num(); i++)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("AI Tank Spawn Point Name: %s"), *allTanks[i]->GetName());*/
		auto tank = Cast<ATank>(allTanks[i]);
		if (tank && tank->MyTankType != ETankType::AITank)
		{
			PlayerTanks.AddUnique(tank);
		}
	}

}

// Called every frame
void AAIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float time = GetWorld()->GetTimeSeconds();
	if (TankToSpawn > 0 && time > NextRoundStartTime && time >= SpawnTime)
	{
		SpawnTime = SpawnIntervalDefault + time;

		SpawnAnAITank();
		TankToSpawn--;	
	}

}

