// Fill out your copyright notice in the Description page of Project Settings.

#include "Co_TankerGameModeBase.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


ACo_TankerGameModeBase::ACo_TankerGameModeBase(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Change the default controller to tank controller
	PlayerControllerClass = ATankController::StaticClass();

	// change defualt flying pawn into tank pawn
	//static ConstructorHelpers::FClassFinder<> PawnClass(TEXT("Blueprint'/Game/Tank/TestTank.TestTank'"))
	//DefaultPawnClass = 

	// this is not needed for now
	//static ConstructorHelpers::FClassFinder<ATankController> VictoryPCOb(TEXT("ATankController"));
	//if ()
	//{

	//}

}
