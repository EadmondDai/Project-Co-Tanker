// ©Eadmond's work. All rights reserved!

#include "TankMovementComponent.h"
#include "TankTrack.h"

// TODO made AI compaticle with energy based move system
void UTankMovementComponent::IntendMoveForward(float val) {
	
	if (!(LeftTrack && RightTrack)) return;
	//UE_LOG(LogTemp, Warning, TEXT("%s movement called, val %f"), *GetOwner()->GetName(),val);
	//float value = FMath::Clamp<float>(val, -1, 1);
	LeftTrack->SetThrottle(val);
	RightTrack->SetThrottle(val);
}

// TODO made AI compaticle with energy based turn system
void UTankMovementComponent::IntendTurnRight(float val)
{
	if (!(LeftTrack && RightTrack)) return;
	//UE_LOG(LogTemp, Warning, TEXT("%s is turning right at val %f"), *GetOwner()->GetName(), val);
	LeftTrack->SetThrottle(val);
	RightTrack->SetThrottle(-val);
}

void UTankMovementComponent::Initialise(UTankTrack * leftTrack, UTankTrack * rightTrack)
{
	if (!(leftTrack && rightTrack)) return;
	LeftTrack = leftTrack;
	RightTrack = rightTrack;
}

void UTankMovementComponent::AddLeftTrackForce(float force, bool isReverseLeftTrack)
{
	if (!LeftTrack)return;
	LeftForcePercent = force;

	bRevertLeftTrack = isReverseLeftTrack;
}

void UTankMovementComponent::AddRightTrackForce(float force, bool isReverseRightTrack)
{
	if (!RightTrack)return;
	RightForcePercent = force;

	bRevertRightTrack = isReverseRightTrack;
}

void UTankMovementComponent::GetEnergyFromEngine(float energy)
{
	CurEnergy = FMath::Clamp<float>(CurEnergy + energy, 0, MaxEnergyCapacity);
}

float UTankMovementComponent::ReleaseEnergyToEngine(float energy)
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

void UTankMovementComponent::BeginPlay()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	ConsumeEnergyByTrack(DeltaTime);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{

	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIMoveIntention = MoveVelocity.GetSafeNormal();

	float ForwardThrottle = FVector::DotProduct(AIMoveIntention, TankForward);
	//UE_LOG(LogTemp, Warning, TEXT("%s is moving towards %f"), *GetOwner()->GetName(), ForwardThrottle);
	IntendMoveForward(ForwardThrottle);

	FVector AIRotate = FVector::CrossProduct(TankForward, AIMoveIntention);
	IntendTurnRight(AIRotate.Z);

}

void UTankMovementComponent::ConsumeEnergyByTrack(float deltaTime)
{
	if (!(RightTrack &&LeftTrack))return;
	// Use absolute value of the force percent to calculate the power.
	float EnergyNeed = (FMath::Abs(RightForcePercent) + FMath::Abs(LeftForcePercent)) / 2 * MaxEnergyConsumePerSercond * deltaTime;

	if (EnergyNeed <= CurEnergy)
	{
		LeftTrack->SetThrottle(LeftForcePercent);
		RightTrack->SetThrottle(RightForcePercent);
		CurEnergy -= EnergyNeed;
	}
}
