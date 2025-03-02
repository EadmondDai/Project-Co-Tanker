// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class CO_TANKER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, Category = Damage)
	float LiveTime = 5.0;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	float Damage = 10;

	// The energy of turret decide if the projectile has full damage.
	UPROPERTY(VisibleAnywhere, Category = Damage)
	float DamageRatio = 1;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float speed, float damageRatio = 1);

private:

	// Used to control how to projectile moves.
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = Component)
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Component)
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Component)
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Component)
	URadialForceComponent* ImpactForce = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DestroyProjectile();
};
