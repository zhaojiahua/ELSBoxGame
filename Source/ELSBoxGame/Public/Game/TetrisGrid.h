#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utilities/MgEnum.h"
#include "TetrisGrid.generated.h"

UCLASS()
class ELSBOXGAME_API ATetrisGrid : public AActor
{
	GENERATED_BODY()

public:
	ATetrisGrid();

protected:
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& propertyChangeEvent)override;

public:
	virtual void Tick(float DeltaTime) override;
	void StartTetrisGame(bool bGameBeginPlay);
	void SpawnNewBlock(bool bIsUseHoldBlock);
	class ATetrisBlockMesh* GetOneNewBlock(FVector inLocation, ETetrisBlock inBlockType);

	//公开的函数
	UFUNCTION(BlueprintCallable, category = "zjhAddGameFuns")
		void GenerateTetrisGrid();
	UFUNCTION(BlueprintPure, category = "zjhAddGameFuns")
		FVector ConverGridIndexToWorldLocation(FVector2D invector);
	UFUNCTION(BlueprintPure, category = "zjhAddGameFuns")
		FVector2D ConverWorldLocationToGridIndex(FVector invector);

	void UpdataBlocksQueue();
	void UpdataBlocksShadow();
	bool AreTheyValidIndex(TArray<FVector2D> inIndexs, TArray<FVector2D> inValidOverride);
	void ReachTheGround();
	void Hold();

	void RemoveFullRows();
	bool IsRowFull(int inRowIndex);
	void DeleteFullRow(int inRowIndex);
	void DecreaseRowsAbove(int inRowIndex);

	void IncreasePoints(ETetrisScore inScoreType);
	void LevelUp();
	void PoolTetrisBlock(class ATetrisBlockMesh* inblock);
	void GameOver();

	//公开的变量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
		float tileSize = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
		float gridWidth = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
		float gridHeight = 10.0f;

	class USceneComponent* RootComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
		class UBillboardComponent* billBordComp;
	TArray<UChildActorComponent*> blocksQueue;
	class ATetrisBlockMesh* oneActiveBlockMesh;
	class UChildActorComponent* tetrisBlockShadowComp;

	TArray<ETetrisBlock> blocksType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs");
	TMap<FVector2D, UStaticMeshComponent*> tetrisGridMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
		TSubclassOf<class ATetrisBlockMesh> blockMesh_BP;

	UPROPERTY(BlueprintReadOnly, category = "zjhAddGameAttrs")
		float currentGameSpeed;
	const float additionalTimeOnGround = 0.2;
	const int maxLevel = 10;

	UPROPERTY(BlueprintReadOnly, category = "zjhAddGameAttrs-score")
		int currentLevel;
	UPROPERTY(BlueprintReadOnly, category = "zjhAddGameAttrs-score")
		int currentCompletedRowCount;
	UPROPERTY(BlueprintReadOnly, category = "zjhAddGameAttrs-score")
		int currentCombo;
	UPROPERTY(BlueprintReadOnly, category = "zjhAddGameAttrs-score")
		int currentPoints;
	UPROPERTY(BlueprintReadOnly, category = "zjhAddGameAttrs-score")
		ETetrisScore lastTetrisScore;

private:
	//私有变量
	class AMgGameMode* gameMode;
	class ATetrisBlockMesh* holdTetrisMesh;
	bool bIsHoldblockAndCurrentblock = false;
	TArray<class ATetrisBlockMesh*> spawnTetrisBlocks;
	TArray<class ATetrisBlockMesh*> pooledTetrisBlocks;

	//私有函数

};