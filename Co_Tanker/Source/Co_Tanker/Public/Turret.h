// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CO_TANKER_API UTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Control)
	void Rotate(float relativeSpeed);

private:
	
	UPROPERTY(EditAnywhere, Category = SetUp)
		float RotateDegreePerSeconds = 5.0;

	UPROPERTY(EditAnywhere, Category = SetUp)
		float MaxRotateDegree = 179;

	UPROPERTY(EditAnywhere, Category = SetUp)
		float MinRotateDegree = -179;
	
};
