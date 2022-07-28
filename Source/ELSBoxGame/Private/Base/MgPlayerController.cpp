#include "Base/MgPlayerController.h"
#include "Base/MgGameMode.h"

AMgPlayerController::AMgPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AMgPlayerController::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AMgGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode) gameMode->playerController = this;
}

void AMgPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMgPlayerController::SetPause(bool inB)
{

}
