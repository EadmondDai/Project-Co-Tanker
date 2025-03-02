// ©Eadmond's work. All rights reserved!

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


float ATank::GetHealthPercent()
{
	return CurHealth / StartHealth;
}

void ATank::SetHealth(float newHealth)
{
	

	CurHealth = newHealth;
	if (CurHealth <= 0)
		OnDeath.Broadcast();
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	CurHealth = StartHealth;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (MyTankType == ETankType::PlayerTankTurret) return 0;
	
	
	int32 damage = FMath::RoundToInt(DamageAmount);
	float realDamage = FMath::Clamp<float>(damage, 0, CurHealth);
	CurHealth -= realDamage;

	if (CurHealth <= 0)
		OnDeath.Broadcast();
	
	// Update health in blueprint in the last
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0;
}

