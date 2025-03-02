// ©Eadmond's work. All rights reserved!

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!Barrel) return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("LaunchPosition"));
	FCollisionResponseParams ResponsParam; // To be discarded
	TArray<AActor*> ActorsToIgnore;

	if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace,
			ResponsParam,
			ActorsToIgnore,
			false
			)
		)
	{
		// Move the barrel to the direction
		AimingDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimingDirection);
		MoveTurretTowards(AimingDirection);

		//UE_LOG(LogTemp, Warning, TEXT("Solution found !"))
	}
}

void UTankAimingComponent::Fire()
{

	if (FireState == EFireState::Reloading) return;
	if (!Barrel) return;

	LastFireTime = GetWorld()->GetTimeSeconds();
	auto projectile = GetWorld()->SpawnActor<AProjectile>(
		Projectile_BP,
		Barrel->GetSocketLocation(FName("LaunchPosition")),
		Barrel->GetSocketRotation(FName("LaunchPosition"))
		);

	// TODO Make energy system work with projectile

	projectile->LaunchProjectile(LaunchSpeed, GetEnergyPercent());

	// reset curEnergy after firing.
	// TODO make the AI work with energy system.
	ATank* myTank = Cast<ATank>(GetOwner());
	if (myTank->MyTankType != ETankType::AITank)
	{
		CurEnergy = 0;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Fire in the hole!"));

}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// Don't try to fire just when the game starts.
	LastFireTime = GetWorld()->GetTimeSeconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime)
	{
		FireState = EFireState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FireState = EFireState::Aiming;
	}
	else
	{
		FireState = EFireState::Locked;
	}
	// TODO aiming and locked states.
}

void UTankAimingComponent::Initialize(UTankBarrel * aBarrel, UTurret * aTurret)
{
	Barrel = aBarrel;
	Turret = aTurret;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!Barrel) return false;
	return !AimingDirection.Equals(Barrel->GetForwardVector().GetSafeNormal(), 0.01);
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
	// Calculate the difference between roration and aimdirectin
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = Direction.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("Barrel Rotator %s, Aim Rotator %s"), *BarrelRotator.ToString(), *AimRotator.ToString());

	// Move the barrel the right amount each frame
	// Using a max roate speed and deltatime.
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector Direction)
{
	if (!Turret) return;

	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimRotator = Direction.Rotation();
	FRotator DeltaRotator = AimRotator - TurretRotator;
	
	float degree = DeltaRotator.Yaw;
	//if (degree < -180) degree += 180;
	//if (degree > 180) degree -= 180;
	//UE_LOG(LogTemp, Warning, TEXT("%s tank is aiming, %f"), *GetOwner()->GetName(), degree);
	if (degree < 180)
		Turret->Rotate(degree);
	else
		Turret->Rotate(-degree);
}

void UTankAimingComponent::GetEnergyFromEngine(float energy)
{
	CurEnergy = FMath::Clamp<float>(CurEnergy + energy, 0, MaxEnergyConsumePerShot);
}

float UTankAimingComponent::ReleaseEnergyToEngine(float energy)
{
	if (CurEnergy > energy)
	{
		CurEnergy -= energy;
		return energy;
	}
	else
	{
		float energyOutput = CurEnergy;
		CurEnergy = 0;
		return energyOutput;
	}
}

