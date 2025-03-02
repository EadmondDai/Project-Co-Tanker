// ©Eadmond's work. All rights reserved!
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "TankBody.h"
//#include "TankTurret.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerState.h"
#include "TankController.generated.h"

class ATank;

/**
 * This class is used to map control of two different player onto their tanks.
 */
UCLASS(config=game)
class CO_TANKER_API ATankController : public APlayerController
{
	GENERATED_BODY()

	ATankController(const FObjectInitializer& ObjectInitializer);
	
	virtual void Tick(float delta) override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnDeath();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerType")
	bool bIsGunner = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrossHair")
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrossHair")
	float CrossHairYLocation = 0.333333;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aim")
	float LineTraceRange = 100000;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	//bool bHasPawn = false;

	//ATankBody* GetControlledTankBody() const;

	//ATankTurret* GetControlledTankTurret() const;

	UFUNCTION(BlueprintCallable, Category = Control)
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	// Start the tank moving the barrel so that a shot would it where the crosshair intersects the world
	void AimAtTheCrosshair();

	// Return an Out paramter, true if hti landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreeLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const;

	UFUNCTION(BlueprintImplementableEvent, Category = DeathEvent)
	void OnDeathBlueprint();

};
