// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/MgUserWidget.h"

#include "Utilities/MgEnum.h"

#include "MgGameBanner.generated.h"

UCLASS()
class ELSBOXGAME_API UMgGameBanner : public UMgUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "zjhAddAttrs")
		EMultiGames bannerName;

	UFUNCTION(BlueprintCallable, Category = "zjhAddFuns")
		void GameButtonClicked();

};
