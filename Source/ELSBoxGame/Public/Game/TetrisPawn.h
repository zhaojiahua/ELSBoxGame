#pragma once

#include "CoreMinimal.h"
#include "Base/MgPawn.h"
#include "TetrisPawn.generated.h"

UCLASS()
class ELSBOXGAME_API ATetrisPawn : public AMgPawn
{
	GENERATED_BODY()

public:
	ATetrisPawn();

protected:
	virtual void BeginPlay() override;



public:
	//公开的变量


	//公开的函数
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetInputForCurrentGame()override;

	virtual void InputLeftRight(float inAxisValue)override;
	virtual void InputUpDown(float inAxisValue)override;
	virtual void InputFirstAction()override;
	virtual void InputSecondAction()override;
	virtual void InputThirdAction()override;

};