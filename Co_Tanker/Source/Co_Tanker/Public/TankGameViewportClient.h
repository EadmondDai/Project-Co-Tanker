// ©Eadmond's work. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "TankGameViewportClient.generated.h"

/**
 * Trying to get different input for different part.
 */
UCLASS()
class CO_TANKER_API UTankGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

	UTankGameViewportClient(const FObjectInitializer& ObjectInitializer);
	
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override
	{
		if (bGamepad)
		{
			//// Assinge different control according to the controllerid
			//if (ControllerId == 0) // player 1 controls how the body move
			//{

			//}
			//else // player 2 controlls how the gun move
			//{

			//}
			return Super::InputKey(Viewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);

		}
		return false;
	}

	virtual bool InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad) override
	{
		if (bGamepad)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ControllerId is %d"), ControllerId);
			//UEngine* const Engine = GetOuterUEngine();
			//int32 const NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
			//bool bRetVal = false;
			//for (int32 i = 0; i < NumPlayers; i++)
			{
				return Super::InputAxis(Viewport, ControllerId, Key, Delta, DeltaTime, NumSamples, bGamepad);
			}
			//return bRetVal;
		}
		return false;
	}

};
