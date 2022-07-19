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
	void SpawnNewBlock();

	//公开的函数
	UFUNCTION(BlueprintCallable, category = "zjhAddGameFuns")
		void GenerateTetrisGrid();
	UFUNCTION(BlueprintPure, category = "zjhAddGameFuns")
		FVector ConverGridIndexToWorldLocation(FVector2D invector);
	UFUNCTION(BlueprintPure, category = "zjhAddGameFuns")
		FVector2D ConverWorldLocationToGridIndex(FVector invector);

	void UpdataBlocksQueue();
	TArray<ETetrisBlock> blocksType;

	//公开的变量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
	float tileSize = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
	float gridWidth = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
	float gridHeight = 10.0f;

	class USceneComponent* RootComp;
	TArray<UChildActorComponent*> blocksQueue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs");
	TMap<FVector2D, UStaticMeshComponent*> tetrisGridMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
		TSubclassOf<class ATetrisBlockMesh> blockMesh_BP;

private:
	//私有变量
	class AMgGameMode* gameMode;

	//私有函数
};
