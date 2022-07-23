#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Utilities/MgEnum.h"

#include "MgGameMode.generated.h"

UCLASS()
class ELSBOXGAME_API AMgGameMode : public AGameMode
{
	GENERATED_BODY()
protected:
	AMgGameMode();
	virtual void InitGameState() override;
	virtual void Tick(float DeltaTime) override;

public:
	//公开的函数
	void SwitchGame(EMultiGames inGame);
	void PlayCurrentGame();
	
	//公开的变量
	EMultiGames currentGame;
	class AMgPlayerController* playerController;
	class AMgHUD* hud;
	class ATetrisGrid* tetrisGrid;
	class AMgPawn* pawn;

protected:
	EMultiGames GetGameFromOpenedLevel();
};
