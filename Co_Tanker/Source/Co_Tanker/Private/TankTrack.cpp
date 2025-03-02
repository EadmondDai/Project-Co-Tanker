// ©Eadmond's work. All rights reserved!

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Engine/World.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

//void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}

void UTankTrack::ApplySidewayForce()
{
	// Calculate splipage speed
	float sideSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// Calculate side acceleration this frame to correct
	float DeltaTime = GetWorld()->GetTimeSeconds();
	auto correctionAccleration = -sideSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways for it.
	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = tankRoot->GetMass() * correctionAccleration / 2; // We have two tracks.
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s is driving at %f"), *GetName(), currentThrottle);
	currentThrottle = FMath::Clamp<float>(currentThrottle, -1, 1);

	// Apply force
	DriveTheTrack();

	// Apply sideforce
	ApplySidewayForce();

	currentThrottle = 0;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float throttle)
{
	currentThrottle += throttle;
}

void UTankTrack::DriveTheTrack()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s, currentThrottle %f"), *GetOwner()->GetName(), currentThrottle);
	auto forceApply = GetForwardVector() * currentThrottle * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApply, forceLocation);
}
