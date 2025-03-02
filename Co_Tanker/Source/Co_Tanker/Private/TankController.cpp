// ©Eadmond's work. All rights reserved!

#include "TankController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "TankAimingComponent.h"
#include "DrawDebugHelpers.h"

ATankController::ATankController(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;


}

void ATankController::Tick(float delta)
{
	Super::Tick(delta);
	if (bIsGunner)
		AimAtTheCrosshair();
	
	return ;
}

void ATankController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	// Player created tanker latter, for the first set pawn, one of the player have only a null pawn.
	ATank* myTank = Cast<ATank>(InPawn);
	if (!myTank) return;
	myTank->OnDeath.AddUniqueDynamic(this, &ATankController::OnDeath);
}

void ATankController::OnDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("Player is dead, Player is dead;"));

	StartSpectatingOnly();

	OnDeathBlueprint();
}

//ATankBody * ATankController::GetControlledTankBody() const
//{
//	return Cast<ATankBody>(GetPawn());
//}
//
//ATankTurret * ATankController::GetControlledTankTurret() const
//{
//	return Cast<ATankTurret>(GetPawn());
//}

ATank * ATankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Player begin play"));
	
}

// This method is for the turret
void ATankController::AimAtTheCrosshair()
{
	if (!GetControlledTank()) return;

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT(" Name is %s HitLocation %s"), *this->GetName(),*HitLocation.ToString());
		GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
	}

}

bool ATankController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	//if (!bIsGunner) return false;

	//OutHitLocation = FVector(1);
	int32 viewportSizeX,  viewportSizeY;
	
	// This is the total viewport size, including two players.
	GetViewportSize(viewportSizeX, viewportSizeY);
	
	FVector2D ScreeLocatoin(viewportSizeX * CrossHairXLocation, viewportSizeY * (CrossHairYLocation * 0.5 + 0.5));
	//UE_LOG(LogTemp, Warning, TEXT(" HitLocation %s"), *ScreeLocatoin.ToString());

	// Find the crosshair position and "De-project" the screen pos to a world direction.
	FVector LookDirection;
	if (GetLookDirection(ScreeLocatoin, LookDirection))
	{
		// Line-trace along that look directoin, and see what we hit(up to max range)
		//FVector camLocation = PlayerCameraManager->GetCameraLocation();
		//FVector camEndLocation = camLocation + LookDirection * LineTraceRange;
		//DrawDebugLine(GetWorld(), camLocation, camEndLocation, FColor::Red, false, 1.0f, 0, 5.f);
		//UE_LOG(LogTemp, Warning, TEXT(" HitLocation %s "), *ScreeLocatoin.ToString());
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	OutHitLocation = FVector(0);
	return false;
}

bool ATankController::GetLookDirection(FVector2D ScreeLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded;
	return DeprojectScreenPositionToWorld(ScreeLocation.X, ScreeLocation.Y, CameraWorldLocation, LookDirection);
		//UE_LOG(LogTemp, Warning, TEXT(" Look direction %s"), *WorldDirection.ToString());
}

bool ATankController::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const
{
	FHitResult OutHit;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	//ECollisionChannel channel = ECC_Visibility;
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Camera))
	{
		OutHitLocation = OutHit.Location;
		return true;
	}
	return false;
	//return GetWorld()->LineTraceMultiByChannel(OutHits, Start, End + LookDirection * distance, ECC_Visibility);

}
