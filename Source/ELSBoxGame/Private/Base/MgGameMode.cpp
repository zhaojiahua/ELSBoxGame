#include "Base/MgGameMode.h"
#include "Kismet/GameplayStatics.h"


AMgGameMode::AMgGameMode()
{

}

void AMgGameMode::InitGameState()
{
	Super::InitGameState();
	currentGame = GetGameFromOpenedLevel();
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
		break;
	case EMultiGames::Game_Multi:
		UGameplayStatics::OpenLevel(this, "LoginMap");
		break;
	case EMultiGames::Game_Tetris:
		UGameplayStatics::OpenLevel(this, "Map_Tetris");
		break;
	case EMultiGames::Game_PacMan:
		UGameplayStatics::OpenLevel(this, "Map_PacMan");
		break;
	}
}

EMultiGames AMgGameMode::GetGameFromOpenedLevel()
{
	EMultiGames tempGame = EMultiGames::Game_None;
	FString levelName = UGameplayStatics::GetCurrentLevelName(this);
	if (levelName == "Map_Tetris") tempGame = EMultiGames::Game_Tetris;
	else if (levelName == "Map_PacMan")  tempGame = EMultiGames::Game_PacMan;
	else if (levelName == "LoginMap") tempGame = EMultiGames::Game_Multi;
	return tempGame;
}
