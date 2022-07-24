#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMultiGames : uint8 
{
	Game_None,
	Game_Multi,
	Game_Tetris,
	Game_PacMan,
};

UENUM(BlueprintType)
enum class EMultiMenu : uint8
{
	Menu_None,
	Menu_Main,
	Menu_Game,
	Menu_Pause,
	Menu_Options,
	Menu_LeaderBoard,
	Menu_GameOver,
};

UENUM(BlueprintType)
enum class EMultiButton : uint8
{
	Button_MainMenu,
	Button_Play,
	Button_Pause,
	Button_Options,
	Button_LeaderBoard,
};

UENUM(BlueprintType)
enum class ETetrisBlock : uint8
{
	I,
	J,
	L,
	O,
	S,
	T,
	Z,
};

UENUM(BlueprintType)
enum class ETetrisScore : uint8
{
	None,
	SingleRow,
	DoubleRow,
	TripleRow,
	Tetris,
	BackToBackTetris,
	SoftDrop,
	HardDrop,
	FullClear,
};
