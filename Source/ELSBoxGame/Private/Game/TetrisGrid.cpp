#include "Game/TetrisGrid.h"
#include "Game/TetrisBlockMesh.h"
#include "Base/MgGameMode.h"
#include "Components/SceneComponent.h"
#include "Components/ChildActorComponent.h"



ATetrisGrid::ATetrisGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;
	for (int16 i = 0; i < 6; i++)
	{
		UChildActorComponent* blockComp = CreateDefaultSubobject<UChildActorComponent>(*("TetrisBlockComp" + FString::FromInt(i + 1)));
		if (blockComp)
		{
			blockComp->SetupAttachment(RootComp);
			blockComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
			blocksQueue.Add(blockComp);
		}
	}
}

void ATetrisGrid::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AMgGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode) gameMode->tetrisGrid = this;
	StartTetrisGame(true);
}

void ATetrisGrid::PostEditChangeProperty(FPropertyChangedEvent& propertyChangeEvent)
{
	Super::PostEditChangeProperty(propertyChangeEvent);
	StartTetrisGame(false);
}


void ATetrisGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATetrisGrid::StartTetrisGame(bool bGameBeginPlay)
{
	GenerateTetrisGrid();
	for (int16 i = 0; i < blocksQueue.Num(); i++)
	{
		blocksQueue[i]->SetRelativeLocation(FVector(0.0f, (gridWidth + 2) * tileSize, gridHeight * tileSize / 6.0f * (i + 0.2)));
	}
	UpdataBlocksQueue();
	if (bGameBeginPlay)
	{
		SpawnNewBlock();
	}
}

void ATetrisGrid::SpawnNewBlock()
{
	//生成方块的位置
	FVector spawnLocation = ConverGridIndexToWorldLocation(FVector2D(FMath::RoundToInt(gridWidth / 2 - 1), FMath::RoundToInt(gridHeight - 3)));
	ETetrisBlock tempblockType = blocksType[5];
	oneActiveBlockMesh = GetOneNewBlock(spawnLocation, tempblockType);
	if (oneActiveBlockMesh) oneActiveBlockMesh->SetBlockActive(true);
	blocksType.RemoveAt(5);
	UpdataBlocksQueue();
}

ATetrisBlockMesh* ATetrisGrid::GetOneNewBlock(FVector inLocation, ETetrisBlock inBlockType)
{
	ATetrisBlockMesh* tempblockMesh = nullptr;
	if (blockMesh_BP)
	{
		tempblockMesh = GetWorld()->SpawnActor<ATetrisBlockMesh>(blockMesh_BP, inLocation, FRotator::ZeroRotator);
		if (tempblockMesh)
		{
			tempblockMesh->tetrisGrid = this;
			tempblockMesh->currentBlock = inBlockType;
			tempblockMesh->SetBlockShape(tileSize);
			tempblockMesh->SetBlockVisual();
		}
	}
	return tempblockMesh;
}

void ATetrisGrid::GenerateTetrisGrid()
{
	tetrisGridMap.Empty();
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			tetrisGridMap.Add(FVector2D(i, j), nullptr);
		}
	}
}

FVector ATetrisGrid::ConverGridIndexToWorldLocation(FVector2D invector)
{
	FVector GridLocation = GetActorLocation();
	float x = GridLocation.X;
	float y = GridLocation.Y + invector.X * tileSize;
	float z = GridLocation.Z + invector.Y * tileSize;
	return FVector(x, y, z);
}

FVector2D ATetrisGrid::ConverWorldLocationToGridIndex(FVector invector)
{
	FVector GridLocation = GetActorLocation();
	int x = FMath::RoundToInt((invector.Y - GridLocation.Y) / tileSize);
	int y = FMath::RoundToInt((invector.Z - GridLocation.Z) / tileSize);
	return FVector2D(x, y);
}

void ATetrisGrid::UpdataBlocksQueue()
{
	while (blocksType.Num() < 8)
	{
		TArray<ETetrisBlock> tempBlockTypes = { ETetrisBlock::I, ETetrisBlock::J,ETetrisBlock::L,ETetrisBlock::O,ETetrisBlock::S,ETetrisBlock::T,ETetrisBlock::Z };
		while (tempBlockTypes.Num() > 0)
		{
			int randomIndex = FMath::RandRange(0, tempBlockTypes.Num() - 1);
			blocksType.Add(tempBlockTypes[randomIndex]);
			tempBlockTypes.RemoveAt(randomIndex);
		}
	}
	if (blockMesh_BP)
	{
		for (int16 i = 0; i < blocksQueue.Num(); i++)
		{
			if (blocksQueue[i])
			{
				ATetrisBlockMesh* blockMeshActor = Cast<ATetrisBlockMesh>(blocksQueue[i]->GetChildActor());
				if (blockMeshActor == nullptr)
				{
					blocksQueue[i]->SetChildActorClass(blockMesh_BP);
					blockMeshActor = Cast<ATetrisBlockMesh>(blocksQueue[i]->GetChildActor());
				}
				if (blockMeshActor)
				{
					blockMeshActor->currentBlock = blocksType[i];
					blockMeshActor->SetBlockShape(tileSize);
					blockMeshActor->SetBlockVisual();
				}
			}
		}
	}
}

bool ATetrisGrid::AreTheyValidIndex(TArray<FVector2D> inIndexs, TArray<FVector2D> inValidOverride)
{
	for (FVector2D itemIndex : inIndexs)
	{
		if (!inValidOverride.Contains(itemIndex))
		{
			if (!tetrisGridMap.Contains(itemIndex))return false;
			else if (tetrisGridMap[itemIndex] != nullptr) return false;
		}
	}
	return true;
}

void ATetrisGrid::ReachTheGround()
{
	if (oneActiveBlockMesh)
	{
		oneActiveBlockMesh->SetBlockActive(false);
		oneActiveBlockMesh = nullptr;
	}
	SpawnNewBlock();
}
