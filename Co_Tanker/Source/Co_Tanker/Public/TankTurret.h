// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankTurret.generated.h"

UCLASS()
class CO_TANKER_API ATankTurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankTurret();

	void AimAt(FVector HitLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
