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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void SwitchGame(EMultiGames inGame);
};
