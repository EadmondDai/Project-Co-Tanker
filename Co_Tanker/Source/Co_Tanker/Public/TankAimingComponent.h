// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTurret;
class AProjectile;
class UTankBarrel;

// Enum for aiming state
UENUM()
enum class EFireState : uint8
{
	Locked,
	Reloading,
	Aiming
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CO_TANKER_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	


	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION()
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Fire)
	void Fire();

	//UFUNCTION(BlueprintImplementable, Category = Fire)
	//void OnFireBlueprint();

	UFUNCTION(BlueprintCallable, Category = SetUp)
	void Initialize(UTankBarrel* aBarrel, UTurret* aTurret);

	bool IsBarrelMoving();

	// unit is second
	UPROPERTY(EditAnywhere, Category = SetUp)
	float ReloadTime = 5.0;

	double LastFireTime = 0;

	UPROPERTY(BlueprintReadOnly, visibleAnywhere, Category = UI)
	EFireState FireState = EFireState::Aiming;

	EFireState GetFireState() { return FireState; }

	UFUNCTION(BlueprintPure, Category = Energy)
	float GetEnergyPercent() { return CurEnergy / MaxEnergyConsumePerShot; }

	void GetEnergyFromEngine(float energy);

	float ReleaseEnergyToEngine(float energy);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// This is the mas power pershot can hold.
	UPROPERTY(EditAnywhere, Category = Energy)
	float MaxEnergyConsumePerShot = 300;

	UPROPERTY(VisibleAnywhere, Category = Energy)
	float CurEnergy = 100;

	UPROPERTY(EditDefaultsOnly, Category = SetUp)
	TSubclassOf<AProjectile> Projectile_BP;

	UPROPERTY(EditAnywhere, Category = Fireing)
	float LaunchSpeed = 10000;

	UPROPERTY(VisibleAnywhere, Category = Fire)
	FVector AimingDirection;

	UPROPERTY(VisibleAnywhere, Category = SetUp)
	UTankBarrel* Barrel = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = SetUp)
	UTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector Direction);

	UFUNCTION(BlueprintCallable, Category = Control)
	void MoveTurretTowards(FVector Direction);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
