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
	void ShowWidget(EMultiGames inGame);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "zjhAddAttrs")
		TSubclassOf<class UMgUserWidget> MgGameWidgetBP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "zjhAddAttrs")
		TSubclassOf<class UMgUserWidget> PacManWidgetBP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "zjhAddAttrs")
		TSubclassOf<class UMgUserWidget> TetrisWidgetBP;

private:
	class AMgGameMode* gameMode;
	class UMgUserWidget* multiGameWidget;
	class UMgUserWidget* pacManGameWidget;
	class UMgUserWidget* tetrisGameWidget;
};
