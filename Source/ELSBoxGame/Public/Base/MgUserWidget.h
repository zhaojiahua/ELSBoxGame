// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/MgEnum.h"
#include "MgUserWidget.generated.h"


UCLASS()
class ELSBOXGAME_API UMgUserWidget : public UUserWidget
{
	GENERATED_BODY()
		virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintNativeEvent, category = "zjhAddFuns")
		void ShowInMenu(EMultiMenu inMenu);
	UFUNCTION(BlueprintCallable, category = "zjhAddFuns")
		void ButtonClicked(EMultiButton inButton);

protected:
	class AMgGameMode* gameMode;
};
