#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TetrisGrid.generated.h"

UCLASS()
class ELSBOXGAME_API ATetrisGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	ATetrisGrid();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	//公开的函数
	UFUNCTION(BlueprintCallable, category = "zjhAddGameFuns")
		void GenerateTetrisGrid(int inGridWidth, int inGridHeight, int inTileSize);
	UFUNCTION(BlueprintPure, category = "zjhAddGameFuns")
		FVector ConverGridIndexToWorldLocation(FVector2D invector);
	UFUNCTION(BlueprintPure, category = "zjhAddGameFuns")
		FVector2D ConverWorldLocationToGridIndex(FVector invector);

	//公开的变量
	float tileSize = 1.0f;
	float gridWidth = 1.0f;
	float gridHeight = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs");
	TMap<FVector2D, UStaticMeshComponent*> tetrisGridMap;
};
