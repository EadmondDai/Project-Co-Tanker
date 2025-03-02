// ©Eadmond's work. All rights reserved!

#include "TankAIController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankAimingComponent.h"

// For now, this function only work with player 1.
ATank * ATankAIController::GetPlayerTank() const
{
	auto firstPlayer = GetWorld()->GetFirstPlayerController();
	if (!firstPlayer) return nullptr;

	auto playerPawn = firstPlayer->GetPawn();
	if (!playerPawn) return nullptr;

	return Cast<ATank>(playerPawn);

}

void ATankAIController::Tick(float delta)
{
	Super::Tick(delta);

	auto tankPawn = GetPlayerTank();
	if (tankPawn)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AI controller find the %s"), *tankBody->GetName());
		MoveToActor(tankPawn, ClosingRadius);

		ATank* myTank = GetControlledTank();
		UTankAimingComponent* aimComponent = myTank->FindComponentByClass<UTankAimingComponent>();
		aimComponent->AimAt(tankPawn->GetActorLocation());

		if(aimComponent->GetFireState() == EFireState::Locked)
			aimComponent->Fire();
	}

}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) return;

		// TODO Subscribe local method to the tank's death event;
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnControlledTankDeath);
	}

}

void ATankAIController::OnControlledTankDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("I am dead, I am dead;"));
	GetPawn()->DetachFromControllerPendingDestroy();

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//auto tankBody = GetPlayerTankBody();
	//auto playercontroller = GetWorld()->GetFirstPlayerController();
	//auto playerPawn = playercontroller->GetPawn();
	//tankBody = Cast<ATankBody>(playerPawn);
	//if (tankBody)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AIController find player : %s"), *tankBody->GetName());
	//}
	//else
	//	UE_LOG(LogTemp, Warning, TEXT("Player tank body not found!"));
}
//
//bool ATankAIController::FindThePlayer()
//{
//
//	return false;
//	
//}
