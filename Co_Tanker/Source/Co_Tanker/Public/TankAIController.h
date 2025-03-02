// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class CO_TANKER_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	ATankAIController(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
	{
		PrimaryActorTick.bCanEverTick = true;
	}

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnType")
	//	bool bIsGunner = false;
	
	virtual void Tick(float delta) override;

	virtual void BeginPlay() override;

	//UFUNCTION(BlueprintCallable, Category = "TEST")
	//bool FindThePlayer();

	//float timeLeft = 5;

private:
	// The raudis towards the plaeyr before stop moving
	UPROPERTY(EditAnywhere, Category = SetUp)
	float ClosingRadius = 30000;

	// I can inline those function later
	ATank* GetPlayerTank() const;

	// I can inline those function later
	ATank* GetControlledTank() const;

	// Called when being possessed by the controller
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnControlledTankDeath();

};
