#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Utilities/MgEnum.h"
#include "MgHUD.generated.h"

UCLASS()
class ELSBOXGAME_API AMgHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	//公开函数
	void ShowWidget(EMultiGames inGame, EMultiMenu inMenu);
	void ButtonClicked(EMultiButton inButton);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "zjhAddAttrs")
		TSubclassOf<class UMgUserWidget> MgGameWidgetBP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "zjhAddAttrs")
		TSubclassOf<class UMgUserWidget> PacManWidgetBP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "zjhAddAttrs")
		TSubclassOf<class UMgUserWidget> TetrisWidgetBP;

	//公开变量
	EMultiMenu currentMenu;

private:
	//私有函数
	void CreateWidgetIfNeed(EMultiGames inGame);
	void HideAllWidgets();

	//私有变量
	class AMgGameMode* gameMode;
	class UMgUserWidget* multiGameWidget;
	class UMgUserWidget* pacManGameWidget;
	class UMgUserWidget* tetrisGameWidget;
};
