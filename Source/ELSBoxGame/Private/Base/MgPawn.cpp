#include "Base/MgPawn.h"
#include "Components/InputComponent.h"
#include "Base/MgGameMode.h"

// Sets default values
AMgPawn::AMgPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMgPawn::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AMgGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode) gameMode->pawn = this;
	SetInputForCurrentGame();
}

void AMgPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Left Right
	sensitivityLeftRightTimer += DeltaTime;
	if (sensitivityLeftRightTimer>=sensitivityLeftRight)
	{
		if (bIsLeftPressed)
		{
			InputLeftRight(-1.0f);
			sensitivityLeftRightTimer = 0.0f;
		}
		else if (bIsRightPressed)
		{
			InputLeftRight(1.0f);
			sensitivityLeftRightTimer = 0.0f;
		}
	}
	//up down
	sensitivityUpDownTimer += DeltaTime;
	if (sensitivityUpDownTimer >= sensitivityLeftRight)
	{
		if (bIsDownPressed)
		{
			InputUpDown(-1.0f);
			sensitivityUpDownTimer = 0.0f;
		}
		else if (bIsUpPressed)
		{
			InputUpDown(1.0f);
			sensitivityUpDownTimer = 0.0f;
		}
	}
}

// Called to bind functionality to input
void AMgPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMgPawn::SetInputForCurrentGame()
{
	//清空inputs
	if (InputComponent)
	{
		for (FInputKeyBinding binding : InputComponent->KeyBindings)
		{
			binding.KeyDelegate.Unbind();
		}
		InputComponent->KeyBindings.Empty();
	}
}

void AMgPawn::InputLeftRight(float inAxisValue)
{

}

void AMgPawn::InputUpDown(float inAxisValue)
{

}

void AMgPawn::InputFirstAction()
{

}

void AMgPawn::InputSecondAction()
{

}

void AMgPawn::InputThirdAction()
{

}

void AMgPawn::InputLeftPressed()
{
	bIsLeftPressed = true;
	bIsRightPressed = false;
}

void AMgPawn::InputLeftReleased()
{
	bIsLeftPressed = false;
	sensitivityLeftRightTimer = sensitivityLeftRight;
}

void AMgPawn::InputRightPressed()
{
	bIsRightPressed = true;
	bIsLeftPressed = false;
}

void AMgPawn::InputRightReleased()
{
	bIsRightPressed = false;
	sensitivityLeftRightTimer = sensitivityLeftRight;
}

void AMgPawn::InputDownPressed()
{
	bIsDownPressed = true;
	bIsUpPressed = false;
}

void AMgPawn::InputDownReleased()
{
	bIsDownPressed = false;
	sensitivityUpDownTimer = sensitivityUpDown;
}

void AMgPawn::InputUpPressed()
{
	bIsUpPressed = true;
	bIsDownPressed = false;
}

void AMgPawn::InputUpReleased()
{
	bIsUpPressed = false;
	sensitivityUpDownTimer = sensitivityUpDown;
}