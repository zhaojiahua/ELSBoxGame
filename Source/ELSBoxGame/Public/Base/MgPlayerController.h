#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MgPlayerController.generated.h"

UCLASS()
class ELSBOXGAME_API AMgPlayerController : public APlayerController
{
	GENERATED_BODY()
	AMgPlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	//公开的函数
	void SetPause(bool inB);

private:
	class AMgGameMode* gameMode;
};
