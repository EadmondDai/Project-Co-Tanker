// ©Eadmond's work. All rights reserved!

#include "TankEngineComponent.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankEngineComponent::UTankEngineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankEngineComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...	
}

void UTankEngineComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *Function)
{
	Super::TickComponent(DeltaTime, TickType, Function);

	float PowerProduced = EnergyProducePerSeconds * DeltaTime;

	// Because order matters here, I can deal with it in their types
	if (!(TankMoveCompRef && TankAimingCompRef)) return;
	if (TankBodyEnergyOperation == 1 && TankTurretEnergyOperation == 1)
	{
		float TankBodyPortion = TankBodyEnergyDrainSpeed / (TankBodyEnergyDrainSpeed + TankTurretEnergyDrainSpeed);
		TankMoveCompRef->GetEnergyFromEngine(PowerProduced * TankBodyPortion);
		TankAimingCompRef->GetEnergyFromEngine((1 - TankBodyPortion) * PowerProduced);
	}
	else if(TankBodyEnergyOperation == -1 && TankTurretEnergyOperation == 1)
	{
		PowerProduced += TankMoveCompRef->ReleaseEnergyToEngine(TankBodyEnergyReleaseSpeed * DeltaTime);
		TankAimingCompRef->GetEnergyFromEngine(PowerProduced);
	}
	else if(TankBodyEnergyOperation == 1 && TankTurretEnergyOperation == -1)
	{
		PowerProduced += TankAimingCompRef->ReleaseEnergyToEngine(TankTurretEnergyReleaseSpeed * DeltaTime);
		TankMoveCompRef->GetEnergyFromEngine(PowerProduced);
	}
	else // It doesn't matter if two parts are both releasing energy or doing nothing.
	{
		if (TankBodyEnergyOperation == 1)
			TankMoveCompRef->GetEnergyFromEngine(PowerProduced);

		if (TankBodyEnergyOperation == -1)
			TankMoveCompRef->ReleaseEnergyToEngine(TankBodyEnergyReleaseSpeed * DeltaTime);

		if (TankTurretEnergyOperation == 1)
			TankAimingCompRef->GetEnergyFromEngine(PowerProduced);

		if (TankTurretEnergyOperation == -1)
			TankAimingCompRef->ReleaseEnergyToEngine(TankTurretEnergyReleaseSpeed * DeltaTime);
	}

	TankBodyEnergyOperation = 0;
	TankTurretEnergyOperation = 0;
}



