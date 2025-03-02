// ©Eadmond's work. All rights reserved!

#include "Projectile.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true); // Hit events
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->SetAutoActivate(false);

	ImpactForce = CreateDefaultSubobject<URadialForceComponent>(FName("ImpactForce"));
	ImpactForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//ImpactForce->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float speed, float damageRatio)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	ProjectileMovementComponent->Activate(true);

	DamageRatio = damageRatio;
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Projectile  on hittttttttttt"));
	//CollisionMesh->Deactivate();
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ImpactForce->FireImpulse();
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		Damage * DamageRatio,
		GetActorLocation(),
		ImpactForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>() // no ignored actor
		);

	FTimerHandle timeHandle;
	GetWorld()->GetTimerManager().SetTimer(timeHandle, this, &AProjectile::DestroyProjectile, LiveTime);
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}

