// ©Eadmond's work. All rights reserved!

#include "Turret.h"


void UTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	auto RotationChange = relativeSpeed * RotateDegreePerSeconds * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Yaw + RotationChange;

	auto Rotation = FMath::Clamp<float>(RawNewElevation, MinRotateDegree, MaxRotateDegree);

	SetRelativeRotation(FRotator(0, Rotation, 0));
}

