// ©Eadmond's work. All rights reserved!

#include "AITank.h"


// Sets default values
AAITank::AAITank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAITank::AimAt(FVector HitLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s is aimming at %s"), *GetName(), *HitLocation.ToString());
}

// Called when the game starts or when spawned
void AAITank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAITank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAITank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

