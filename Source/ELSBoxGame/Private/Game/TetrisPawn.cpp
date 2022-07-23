#include "Game/TetrisPawn.h"
#include "Game/TetrisGrid.h"
#include "Game/TetrisBlockMesh.h"
#include "Base/MgGameMode.h"
#include "Framework/Commands/InputChord.h"
#include "Components/InputComponent.h"

ATetrisPawn::ATetrisPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATetrisPawn::BeginPlay()
{
	Super::BeginPlay();

}

void ATetrisPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATetrisPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATetrisPawn::SetInputForCurrentGame()
{
	Super::SetInputForCurrentGame(); //reset inputs
	if (InputComponent)
	{
		InputComponent->BindKey(EKeys::Left, IE_Pressed, this, &AMgPawn::InputLeftPressed);
		InputComponent->BindKey(EKeys::Left, IE_Released, this, &AMgPawn::InputLeftReleased);
		InputComponent->BindKey(EKeys::Right, IE_Pressed, this, &AMgPawn::InputRightPressed);
		InputComponent->BindKey(EKeys::Right, IE_Released, this, &AMgPawn::InputRightReleased);
		InputComponent->BindKey(EKeys::Up, IE_Pressed, this, &AMgPawn::InputUpPressed);
		InputComponent->BindKey(EKeys::Up, IE_Released, this, &AMgPawn::InputUpReleased);
		InputComponent->BindKey(EKeys::Down, IE_Pressed, this, &AMgPawn::InputDownPressed);
		InputComponent->BindKey(EKeys::Down, IE_Released, this, &AMgPawn::InputDownReleased);
		//Actions
		InputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &AMgPawn::InputFirstAction);//Hard Drop
		InputComponent->BindKey(EKeys::Up, IE_Pressed, this, &AMgPawn::InputSecondAction);//Rotate
		InputComponent->BindKey(EKeys::RightShift, IE_Pressed, this, &AMgPawn::InputThirdAction);//hold
	}
}

void ATetrisPawn::InputLeftRight(float inAxisValue)
{
	Super::InputLeftRight(inAxisValue);
	if (gameMode)
	{
		if (gameMode->tetrisGrid)
		{
			if (gameMode->tetrisGrid->oneActiveBlockMesh)
			{
				if (inAxisValue < 0.0f)
				{
					//left moves
					gameMode->tetrisGrid->oneActiveBlockMesh->MoveSelfLeft();
				}
				else if (inAxisValue > 0.0f)
				{
					//Right Move
					gameMode->tetrisGrid->oneActiveBlockMesh->MoveSelfRight();
				}
			}
		}
	}
}

void ATetrisPawn::InputUpDown(float inAxisValue)
{
	Super::InputUpDown(inAxisValue);
	if (gameMode)
	{
		if (gameMode->tetrisGrid)
		{
			if (gameMode->tetrisGrid->oneActiveBlockMesh)
			{
				if (inAxisValue < 0.0f)
					gameMode->tetrisGrid->oneActiveBlockMesh->MoveSelfDown();
			}
		}
	}
}

void ATetrisPawn::InputFirstAction()
{
	Super::InputFirstAction();
	if (gameMode)
	{
		if (gameMode->tetrisGrid)
		{
			if (gameMode->tetrisGrid->oneActiveBlockMesh)
				gameMode->tetrisGrid->oneActiveBlockMesh->HardDrop();
		}
	}
}

void ATetrisPawn::InputSecondAction()
{
	Super::InputSecondAction();
	if (gameMode)
	{
		if (gameMode->tetrisGrid)
		{
			if (gameMode->tetrisGrid->oneActiveBlockMesh)
				gameMode->tetrisGrid->oneActiveBlockMesh->RotateSelf();
		}
	}
}

void ATetrisPawn::InputThirdAction()
{
	Super::InputThirdAction();
	if (gameMode)
	{
		if (gameMode->tetrisGrid)
		{
			if (gameMode->tetrisGrid->oneActiveBlockMesh)
				gameMode->tetrisGrid->Hold();
		}
	}
}

