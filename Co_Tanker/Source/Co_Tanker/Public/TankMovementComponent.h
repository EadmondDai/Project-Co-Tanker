// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

//class ATank;
class UTankTrack;

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class CO_TANKER_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Input)
	bool bRevertLeftTrack = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Input)
	bool bRevertRightTrack = false;

	// Used for update UI
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Input)
	float LeftForcePercent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Input)
	float RightForcePercent;

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float val);
	
	// -1 anti clockwise, 1 clock wise
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float val);

	UFUNCTION(BlueprintCallable, Category = SetUp)
	void Initialise(UTankTrack *leftTrack, UTankTrack* rightTrack);

	UFUNCTION(BlueprintPure, Category = Energy)
	float GetEnergyPercent() { return CurEnergy / MaxEnergyCapacity; }

	UFUNCTION(BlueprintCallable, Category = Input)
	void AddLeftTrackForce(float force, bool isReverseLeftTrack);

	UFUNCTION(BlueprintCallable, Category = Input)
	void AddRightTrackForce(float force, bool isReverseRightTrack);

	void GetEnergyFromEngine(float energy);

	float ReleaseEnergyToEngine(float energy);

private:
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, Category = Energy)
	float MaxEnergyCapacity = 2000;

	// This is max consumption for both track working at maxmiam power.
	UPROPERTY(EditAnywhere, Category = Energy)
	float MaxEnergyConsumePerSercond = 300;

	UPROPERTY(VisibleAnywhere, Category = Energy)
	float CurEnergy = 0;

	UPROPERTY(VisibleAnywhere, Category = Move)
	UTankTrack* LeftTrack = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Move)
	UTankTrack* RightTrack = nullptr;

	// Called from the pathfinding logic by the AI controller.
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	// decide how much energy left and right track comsume.
	void ConsumeEnergyByTrack(float deltaTime);

};
