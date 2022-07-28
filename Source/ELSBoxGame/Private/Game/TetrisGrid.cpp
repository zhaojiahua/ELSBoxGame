#include "Game/TetrisGrid.h"
#include "Game/TetrisBlockMesh.h"
#include "Base/MgGameMode.h"
#include "Components/SceneComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/BillboardComponent.h"
#include "Base/MgHUD.h"
#include "Base/MgUserWidget.h"



ATetrisGrid::ATetrisGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	billBordComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("billBordComp"));
	tetrisBlockShadowComp= CreateDefaultSubobject<UChildActorComponent>(TEXT("tetrisBlockShadowComp"));

	RootComponent = RootComp;
	billBordComp->SetupAttachment(RootComp);
	tetrisBlockShadowComp->SetupAttachment(RootComp);
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
	currentLevel = 1;
	currentCompletedRowCount=0;
	currentCombo = 0;
	currentPoints = 0;
	lastTetrisScore = ETetrisScore::None;
	currentGameSpeed = 1.0f;
	oneActiveBlockMesh = nullptr;
	holdTetrisMesh = nullptr;

	if (gameMode&&gameMode->hud&&gameMode->hud->GetWidget(EMultiGames::Game_Tetris))
	{
		gameMode->hud->GetWidget(EMultiGames::Game_Tetris)->UpdataPoints(currentPoints);
		gameMode->hud->GetWidget(EMultiGames::Game_Tetris)->UpdataCombo(currentCombo);
		gameMode->hud->GetWidget(EMultiGames::Game_Tetris)->UpdataLevel(currentLevel);
		gameMode->hud->GetWidget(EMultiGames::Game_Tetris)->UpdataProgression(currentCompletedRowCount);
	}

	GenerateTetrisGrid();
	for (int16 i = 0; i < blocksQueue.Num(); i++)
	{
		blocksQueue[i]->SetRelativeLocation(FVector(0.0f, (gridWidth + 2) * tileSize, gridHeight * tileSize / 6.0f * (i + 0.2)));
	}
	billBordComp->SetRelativeLocation(FVector(0.0f, -4 * tileSize, gridHeight * tileSize / 6.0f * 5.0f));
	UpdataBlocksQueue();
	if (bGameBeginPlay)
		SpawnNewBlock(false);
}

void ATetrisGrid::SpawnNewBlock(bool bIsUseHoldBlock)
{
	//生成方块的位置
	FVector spawnLocation = ConverGridIndexToWorldLocation(FVector2D(FMath::RoundToInt(gridWidth / 2 - 1), FMath::RoundToInt(gridHeight - 2)));
	if (!bIsUseHoldBlock)
	{
		ETetrisBlock tempblockType = blocksType[0];
		oneActiveBlockMesh = GetOneNewBlock(spawnLocation, tempblockType);
		if (oneActiveBlockMesh) oneActiveBlockMesh->SetBlockActive(true);
		blocksType.RemoveAt(0);
		UpdataBlocksQueue();
		bIsHoldblockAndCurrentblock = false;
	}
	else
	{
		oneActiveBlockMesh = holdTetrisMesh;
		if (oneActiveBlockMesh)	oneActiveBlockMesh->SetActorLocation(spawnLocation);
	}
	UpdataBlocksShadow();
	if (oneActiveBlockMesh)
	{
		TArray<FVector2D> spawnBlockIndexs = oneActiveBlockMesh->GetGridIndexs(FVector2D(0.0f));
		if (AreTheyValidIndex(spawnBlockIndexs, TArray<FVector2D>()))
		{
			tetrisGridMap.Add(spawnBlockIndexs[0], oneActiveBlockMesh->staticMeshComp1);
			tetrisGridMap.Add(spawnBlockIndexs[1], oneActiveBlockMesh->staticMeshComp2);
			tetrisGridMap.Add(spawnBlockIndexs[2], oneActiveBlockMesh->staticMeshComp3);
			tetrisGridMap.Add(spawnBlockIndexs[3], oneActiveBlockMesh->staticMeshComp4);
			oneActiveBlockMesh->SetBlockActive(true);
		}
		else
		{
			oneActiveBlockMesh->SetBlockActive(false);
			GameOver();
		}
	}
}

ATetrisBlockMesh* ATetrisGrid::GetOneNewBlock(FVector inLocation, ETetrisBlock inBlockType)
{
	ATetrisBlockMesh* tempblockMesh = nullptr;
	if (blockMesh_BP)
	{
		if (pooledTetrisBlocks.Num()>0)
		{
			tempblockMesh = pooledTetrisBlocks[0];
			pooledTetrisBlocks.RemoveAt(0);
			if (tempblockMesh)
			{
				tempblockMesh->SetActorLocationAndRotation(inLocation, FRotator::ZeroRotator);
				tempblockMesh->staticMeshComp1->SetHiddenInGame(false);
				tempblockMesh->staticMeshComp2->SetHiddenInGame(false);
				tempblockMesh->staticMeshComp3->SetHiddenInGame(false);
				tempblockMesh->staticMeshComp4->SetHiddenInGame(false);
			}
		}
		else
		{
			tempblockMesh = GetWorld()->SpawnActor<ATetrisBlockMesh>(blockMesh_BP, inLocation, FRotator::ZeroRotator);
			if (tempblockMesh)		spawnTetrisBlocks.Add(tempblockMesh);
		}
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
	for (ATetrisBlockMesh* tetrisBlock:spawnTetrisBlocks)
	{
		PoolTetrisBlock(tetrisBlock);
	}
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

void ATetrisGrid::UpdataBlocksShadow()
{
	if (blockMesh_BP)
	{
		if (tetrisBlockShadowComp)
		{
			ATetrisBlockMesh* tempActor = Cast<ATetrisBlockMesh>(tetrisBlockShadowComp->GetChildActor());
			if (tempActor==nullptr)
			{
				tetrisBlockShadowComp->SetChildActorClass(blockMesh_BP);
				tempActor = Cast<ATetrisBlockMesh>(tetrisBlockShadowComp->GetChildActor());
			}
			if (tempActor&&oneActiveBlockMesh)
			{
				tempActor->tetrisGrid = this;
				tempActor->currentBlock = oneActiveBlockMesh->currentBlock;
				tempActor->bIsShadow = true;
				tempActor->SetBlockShape(tileSize);
				tempActor->SetActorTransform(oneActiveBlockMesh->GetActorTransform());

				TArray<FVector2D> initialGridIndexs = tempActor->GetGridIndexs(FVector2D(0.0f));
				while (AreTheyValidIndex(tempActor->GetGridIndexs(FVector2D(0.0f,-1.0f)), initialGridIndexs))
				{
					tempActor->AddActorWorldOffset(FVector(0.0f, 0.0f, -1.0 * tileSize));
				}
				tempActor->AddActorWorldOffset(FVector(20.0f, 0.0f, 0.0f));
				tempActor->SetBlockVisual();
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
	RemoveFullRows();
	SpawnNewBlock(false);
}

void ATetrisGrid::Hold()
{
	if (!bIsHoldblockAndCurrentblock)
	{
		bIsHoldblockAndCurrentblock = true;
		ATetrisBlockMesh* currentBlockMesh = oneActiveBlockMesh;
		if (currentBlockMesh)
		{
			currentBlockMesh->SetBlockActive(false);
			TArray< FVector2D> currentIndexs = currentBlockMesh->GetGridIndexs(FVector2D(0.0f, 0.0f));
			tetrisGridMap.Add(currentIndexs[0], nullptr);
			tetrisGridMap.Add(currentIndexs[1], nullptr);
			tetrisGridMap.Add(currentIndexs[2], nullptr);
			tetrisGridMap.Add(currentIndexs[3], nullptr);

			if (billBordComp)
			{
				currentBlockMesh->SetActorLocation(billBordComp->GetComponentLocation());
				currentBlockMesh->SetActorRotation(FRotator(0.0f));
			}
		}
		SpawnNewBlock(holdTetrisMesh != nullptr);
		holdTetrisMesh = currentBlockMesh;
	}
}

void ATetrisGrid::RemoveFullRows()
{
	int tempCompeleteRowCount = 0;
	for (int Y=0;Y<gridHeight;Y++)
	{
		if (IsRowFull(Y))
		{
			DeleteFullRow(Y);
			DecreaseRowsAbove(Y);
			Y--;
			currentCompletedRowCount++;
			tempCompeleteRowCount++;
			if (currentCompletedRowCount % 10 == 0)	LevelUp();
		}
	}
	if (tempCompeleteRowCount > 0)
	{
		currentCombo++;

		switch (tempCompeleteRowCount)
		{
		case 1:
			IncreasePoints(ETetrisScore::SingleRow);
			break;
		case 2:
			IncreasePoints(ETetrisScore::DoubleRow);
			break;
		case 3:
			IncreasePoints(ETetrisScore::TripleRow);
			break;
		case 4:
			if (lastTetrisScore == ETetrisScore::Tetris || lastTetrisScore == ETetrisScore::BackToBackTetris)
			{
				IncreasePoints(ETetrisScore::BackToBackTetris);
			}
			else IncreasePoints(ETetrisScore::Tetris);
			break;
		default:
			break;
		}
		bool isFullClear = true;
		for (int x = 0; x < gridWidth; x++)
		{
			if (tetrisGridMap[FVector2D(x,0)]!=nullptr)
			{
				isFullClear = false;
				break;
			}
		}
		if (isFullClear)	IncreasePoints(ETetrisScore::FullClear);
	}
	else
	{
		currentCombo = 0;
		lastTetrisScore = ETetrisScore::None;
	}
	if (gameMode && gameMode->hud && gameMode->hud->GetWidget(EMultiGames::Game_Tetris))
	{
		gameMode->hud->GetWidget(EMultiGames::Game_Tetris)->UpdataCombo(currentCombo);
		gameMode->hud->GetWidget(EMultiGames::Game_Tetris)->UpdataProgression(currentLevel == maxLevel ? 1.0f : currentCompletedRowCount % 10 / 10.f);
	}
}

bool ATetrisGrid::IsRowFull(int inRowIndex)
{
	for (int x =0;x<gridWidth;x++)
	{
		if (tetrisGridMap.Contains(FVector2D(x,inRowIndex)))
		{
			if (tetrisGridMap[FVector2D(x, inRowIndex)] == nullptr) return false;
		}
	}
	return true;
}

void ATetrisGrid::DeleteFullRow(int inRowIndex)
{
	for (int x=0;x<gridWidth;x++)
	{
		tetrisGridMap[FVector2D(x, inRowIndex)]->SetHiddenInGame(true);
		ATetrisBlockMesh* tetrisblock = Cast<ATetrisBlockMesh>(tetrisGridMap[FVector2D(x, inRowIndex)]->GetOwner());
		if (tetrisblock)
		{
			if (tetrisblock->staticMeshComp1->bHiddenInGame&& tetrisblock->staticMeshComp2->bHiddenInGame&& tetrisblock->staticMeshComp3->bHiddenInGame&& tetrisblock->staticMeshComp4->bHiddenInGame)
				PoolTetrisBlock(tetrisblock);
		}
		tetrisGridMap.Add(FVector2D(x, inRowIndex), nullptr);
	}
}

void ATetrisGrid::DecreaseRowsAbove(int inRowIndex)
{
	for (int y = inRowIndex+1; y < gridHeight; y++)
	{
		for (int x=0;x<gridWidth;x++)
		{
			if (tetrisGridMap[FVector2D(x, y)])
			{
				tetrisGridMap[FVector2D(x, y)]->AddWorldOffset(FVector(0.0f, 0.0f, -1.0f * tileSize));
				tetrisGridMap.Add(FVector2D(x, y - 1), tetrisGridMap[FVector2D(x, y)]);
				tetrisGridMap.Add(FVector2D(x, y), nullptr);
			}
		}
	}
}

void ATetrisGrid::IncreasePoints(ETetrisScore inScoreType)
{
	switch (inScoreType)
	{
	case ETetrisScore::SingleRow:
		currentPoints += 10 * currentLevel + 2 * currentCombo * currentLevel;
		break;
	case ETetrisScore::DoubleRow:
		currentPoints += 20 * currentLevel + 5 * currentCombo * currentLevel;
		break;
	case ETetrisScore::TripleRow:
		currentPoints += 40 * currentLevel + 5 * currentCombo * currentLevel;
		break;
	case ETetrisScore::Tetris:
		currentPoints += 80 * currentLevel + 5 * currentCombo * currentLevel;
		break;
	case ETetrisScore::BackToBackTetris:
		currentPoints += 150 * currentLevel + 5 * currentCombo * currentLevel;
		break;
	case ETetrisScore::SoftDrop:
		currentPoints += 1;
		break;
	case ETetrisScore::HardDrop:
		currentPoints += 20; 
		break;
	case ETetrisScore::FullClear:
		currentPoints += 300 * currentLevel;
		break;
	default:
		break;
	}
	if (inScoreType !=ETetrisScore::SoftDrop&&inScoreType !=ETetrisScore::HardDrop)
	{
		lastTetrisScore = inScoreType;
	}
	if (gameMode && gameMode->hud && gameMode->hud->GetWidget(EMultiGames::Game_Tetris))
	{
		gameMode->hud->GetWidget(EMultiGames::Game_Tetris)->UpdataPoints(currentPoints);
	}
}

void ATetrisGrid::LevelUp()
{
	if (currentLevel<maxLevel)
	{
		currentLevel++;
		currentGameSpeed -= currentGameSpeed / 3.0f;
		if (gameMode && gameMode->hud && gameMode->hud->GetWidget(EMultiGames::Game_Tetris))
		{
			gameMode->hud->GetWidget(EMultiGames::Game_Tetris)->UpdataLevel(currentLevel);
		}
	}
}

void ATetrisGrid::PoolTetrisBlock(class ATetrisBlockMesh* inblock)
{
	if (inblock)
	{
		inblock->SetBlockActive(false);
		inblock->staticMeshComp1->SetHiddenInGame(true);
		inblock->staticMeshComp2->SetHiddenInGame(true);
		inblock->staticMeshComp3->SetHiddenInGame(true);
		inblock->staticMeshComp4->SetHiddenInGame(true);
		pooledTetrisBlocks.AddUnique(inblock);
	}
}

void ATetrisGrid::GameOver()
{
	StartTetrisGame(true);
}

