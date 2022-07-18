﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utilities/MgEnum.h"
#include "TetrisBlockMesh.generated.h"

UCLASS()
class ELSBOXGAME_API ATetrisBlockMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	ATetrisBlockMesh();

protected:
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& propertyChangeEvent)override;

public:	
	virtual void Tick(float DeltaTime) override;


	//公开函数
	void SetBlockVisual();
	void SetBlockShape(float inTileSize);

	//公开变量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "zjhAddGameAttrs")
		class USceneComponent* RootComp;
	
	class UStaticMeshComponent* staticMeshComp1;
	class UStaticMeshComponent* staticMeshComp2;
	class UStaticMeshComponent* staticMeshComp3;
	class UStaticMeshComponent* staticMeshComp4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddGameAttrs")
		UStaticMesh* blockMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddGameAttrs")
		UMaterialInterface* blockMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddGameAttrs")
		ETetrisBlock currentBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddGameAttrs")
		FLinearColor color_I;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddGameAttrs")
		FLinearColor color_J;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddGameAttrs")
		FLinearColor color_L;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddGameAttrs")
		FLinearColor color_O;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddGameAttrs")
		FLinearColor color_S;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddGameAttrs")
		FLinearColor color_T;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddGameAttrs")
		FLinearColor color_Z;

private:
	UMaterialInstanceDynamic* blockMaterialDyn;
	class AMgGameMode* gameMode;
};