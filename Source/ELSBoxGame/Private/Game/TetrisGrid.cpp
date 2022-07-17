#include "Game/TetrisGrid.h"
#include "Components/SceneComponent.h"


ATetrisGrid::ATetrisGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;
}

void ATetrisGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATetrisGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATetrisGrid::GenerateTetrisGrid(int inGridWidth, int inGridHeight, int inTileSize)
{
	tetrisGridMap.Empty();
	gridWidth = inGridWidth;
	gridHeight = inGridHeight;
	tileSize = inTileSize;
	for (int i =0 ; i < inGridWidth; i++)
	{
		for (int j = 0; j < inGridHeight; j++)
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

