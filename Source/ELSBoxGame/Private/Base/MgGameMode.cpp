#include "Base/MgGameMode.h"
#include "Kismet/GameplayStatics.h"


AMgGameMode::AMgGameMode()
{

}

void AMgGameMode::BeginPlay()
{

}

void AMgGameMode::Tick(float DeltaTime)
{

}

void AMgGameMode::SwitchGame(EMultiGames inGame)
{
	switch (inGame)
	{
	default:
	case EMultiGames::Game_None:
	case EMultiGames::Game_Multi:
		break;
	case EMultiGames::Game_Tetris:
		UGameplayStatics::OpenLevel(this, "Map_Tetris");
		break;
	case EMultiGames::Game_PacMan:
		UGameplayStatics::OpenLevel(this, "Map_PacMan");
		break;
	}
}
