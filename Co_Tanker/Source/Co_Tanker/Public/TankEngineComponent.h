// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankEngineComponent.generated.h"

class UTankMovementComponent;
class UTankAimingComponent;

UENUM(BlueprintType)
enum class ETankEnergyOperationType : uint8
{
	TankBodyDrain         UMETA(DisplayName = "TankBodyDrain"),
	TankBodyRelease	   UMETA(DisplayName = "TankBodyRelease"),
	TankTurretDrain			       UMETA(DisplayName = "TankTurretDrain"),
	TankTurretRelease			       UMETA(DisplayName = "TankTurretRelease")
};

/**
* Used to distribute energy between tank movemoment component and tank aiming component
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CO_TANKER_API UTankEngineComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// Target move comp ref, for player it should be on the tank body
	UPROPERTY(VisibleAnywhere, Category = Energy)
	UTankMovementComponent* TankMoveCompRef = nullptr;

	// Target aim comp ref, for player it should be on the tank turret
	UPROPERTY(VisibleAnywhere, Category = Energy)
	UTankAimingComponent* TankAimingCompRef = nullptr;

	UPROPERTY(EditAnywhere, Category = Energy)
	float EnergyProducePerSeconds = 300;

	UPROPERTY(EditDefaultsOnly, Category = Energy)
	float TankBodyEnergyDrainSpeed = 200;

	UPROPERTY(EditDefaultsOnly, Category = Energy)
	float TankBodyEnergyReleaseSpeed = 600;

	UPROPERTY(EditDefaultsOnly, Category = Energy)
	float TankTurretEnergyDrainSpeed = 200;

	UPROPERTY(EditDefaultsOnly, Category = Energy)
	float TankTurretEnergyReleaseSpeed = 600;

	// -1 release, 1 drain, 0 neutral;
	UPROPERTY(VisibleAnywhere, Category = Energy)
	int TankBodyEnergyOperation = 0;

	// -1 release, 1 drain, 0 neutral;
	UPROPERTY(VisibleAnywhere, Category = Energy)
	int TankTurretEnergyOperation = 0;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *Function);

public:	
	// Sets default values for this component's properties
	UTankEngineComponent();

	UFUNCTION(BlueprintCallable, Category = Energy)
	void SetTankEnergyOperationType(ETankEnergyOperationType tankOperationType)
	{
		switch (tankOperationType)
		{
		case ETankEnergyOperationType::TankBodyDrain:
			TankBodyEnergyOperation += 1;
			break;
		case ETankEnergyOperationType::TankBodyRelease:
			TankBodyEnergyOperation += -1;
			break;
		case ETankEnergyOperationType::TankTurretDrain:
			TankTurretEnergyOperation += 1;
			break;
		case ETankEnergyOperationType::TankTurretRelease:
			TankTurretEnergyOperation += -1;
			break;
		default:
			TankBodyEnergyOperation = 0;
			TankTurretEnergyOperation = 0;
			break;
		}
	}


	UFUNCTION(BlueprintCallable, Category = Energy)
	void SetTankMoveCompRef(UTankMovementComponent* MoveCompRef) { TankMoveCompRef = MoveCompRef; }

	UFUNCTION(BlueprintCallable, Category = Energy)	
	void SetTankAimingCompRef(UTankAimingComponent* AimCompRef) { TankAimingCompRef = AimCompRef; }
		
	
};
