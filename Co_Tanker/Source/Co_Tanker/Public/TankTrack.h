// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CO_TANKER_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	UTankTrack();

	float currentThrottle = 0;

	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ApplySidewayForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure, Category = Energy)
	float GetThrottlePercent() { return FMath::Clamp<float>(currentThrottle, 0, 1); }

	// Set a throttle between 0 to 1.
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float throttle);

	void DriveTheTrack();
	
	// Max force per track in newtons
	UPROPERTY(EditDefaultsOnly, Category = SetUp)
	float TrackMaxDrivingForce = 400000; // Assume 40 ton tank, 10g driving force

};
