// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UENUM(BlueprintType)
enum class ETankType : uint8
{
	PlayerTankBody         UMETA(DisplayName = "PlayerTank"),
	PlayerTankTurret	   UMETA(DisplayName = "PlayerGunner"),
	AITank			       UMETA(DisplayName = "AITank")
};

// Declare tank delegate for OnDeath event;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class CO_TANKER_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Enum)
	ETankType MyTankType;

	FTankDelegate OnDeath;

	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent();

	UFUNCTION(BlueprintPure, Category = Health)
	float GetCurHealth() { return CurHealth; }

	float GetStartHealth() { return StartHealth; }

	// Used to synchronize health from the tank body
	UFUNCTION(BlueprintCallable, Category = Health)
	void SetHealth(float newHealth);

protected:
	UPROPERTY(EditDefaultsOnly, Category = Health)
	float StartHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Health)
	float CurHealth = StartHealth;

	UPROPERTY(EditDefaultsOnly, Category = Health)
	float MaxHealth = 150;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Called by the engine's damage system
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
