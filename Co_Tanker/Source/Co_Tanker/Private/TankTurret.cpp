// ©Eadmond's work. All rights reserved!

#include "TankTurret.h"


// Sets default values
ATankTurret::ATankTurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATankTurret::AimAt(FVector HitLocation)
{


}

// Called when the game starts or when spawned
void ATankTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

