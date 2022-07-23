#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MgPawn.generated.h"

UCLASS()
class ELSBOXGAME_API AMgPawn : public APawn
{
	GENERATED_BODY()

public:
	AMgPawn();

protected:
	virtual void BeginPlay() override;

	//受保护变量
	float sensitivityLeftRightTimer = 0.0f;
	float sensitivityUpDownTimer = 0.0f;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetInputForCurrentGame();

	virtual void InputLeftRight(float inAxisValue);
	virtual void InputUpDown(float inAxisValue);
	virtual void InputFirstAction();
	virtual void InputSecondAction();
	virtual void InputThirdAction();

	void InputLeftPressed();
	void InputLeftReleased();
	void InputRightPressed();
	void InputRightReleased();
	void InputDownPressed();
	void InputDownReleased();
	void InputUpPressed();
	void InputUpReleased();

	//公开的变量
	bool bIsLeftPressed = false;
	bool bIsRightPressed = false;
	bool bIsDownPressed = false;
	bool bIsUpPressed = false;
	float sensitivityLeftRight = 0.15f;
	float sensitivityUpDown = 0.15f;

	class AMgGameMode* gameMode;
};
