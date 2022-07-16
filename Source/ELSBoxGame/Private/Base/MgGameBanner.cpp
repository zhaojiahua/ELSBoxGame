// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/MgGameBanner.h"
#include "Base/MgGameMode.h"


void UMgGameBanner::GameButtonClicked()
{
	if (gameMode)
	{
		gameMode->SwitchGame(bannerName);
	}
}
