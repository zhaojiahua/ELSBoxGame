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

private:
	class AMgGameMode* gameMode;
};
