// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankBody.generated.h"

UCLASS()
class CO_TANKER_API ATankBody : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankBody();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
