#include "Game/TetrisBlockMesh.h"
#include "Game/TetrisGrid.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Base/MgGameMode.h"

ATetrisBlockMesh::ATetrisBlockMesh()
{
 	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;
	staticMeshComp1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMeshComp1"));
	staticMeshComp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMeshComp2"));
	staticMeshComp3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMeshComp3"));
	staticMeshComp4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMeshComp4"));
	staticMeshComp1->SetupAttachment(RootComp);
	staticMeshComp2->SetupAttachment(RootComp);
	staticMeshComp3->SetupAttachment(RootComp);
	staticMeshComp4->SetupAttachment(RootComp);

	SetBlockVisual();
}

void ATetrisBlockMesh::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AMgGameMode>(GetWorld()->GetAuthGameMode());
}

void ATetrisBlockMesh::PostEditChangeProperty(FPropertyChangedEvent& propertyChangeEvent)
{
	Super::PostEditChangeProperty(propertyChangeEvent);
	SetBlockVisual();
	SetBlockShape(100.0f);
}

void ATetrisBlockMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isActive) DropDownWithTime(DeltaTime);
}

void ATetrisBlockMesh::SetBlockVisual()
{
	if (blockMesh)
	{
		staticMeshComp1->SetStaticMesh(blockMesh);
		staticMeshComp2->SetStaticMesh(blockMesh);
		staticMeshComp3->SetStaticMesh(blockMesh);
		staticMeshComp4->SetStaticMesh(blockMesh);

		if (blockMaterial)
		{
			if (blockMaterialDyn == nullptr)
			{
				blockMaterialDyn = UMaterialInstanceDynamic::Create(blockMaterial, this, TEXT("blockMaterial"));
				staticMeshComp1->SetMaterial(0, blockMaterialDyn);
				staticMeshComp2->SetMaterial(0, blockMaterialDyn);
				staticMeshComp3->SetMaterial(0, blockMaterialDyn);
				staticMeshComp4->SetMaterial(0, blockMaterialDyn);
			}
			if (blockMaterialDyn)
			{
				FLinearColor tempColor;
				switch (currentBlock)
				{
				case ETetrisBlock::I:
					tempColor = color_I;
					break;
				case ETetrisBlock::J:
					tempColor = color_J;
					break;
				case ETetrisBlock::L:
					tempColor = color_L;
					break;
				case ETetrisBlock::O:
					tempColor = color_O;
					break;
				case ETetrisBlock::S:
					tempColor = color_S;
					break;
				case ETetrisBlock::T:
					tempColor = color_T;
					break;
				case ETetrisBlock::Z:
					tempColor = color_Z;
					break;
				default:
					break;
				}
				blockMaterialDyn->SetVectorParameterValue("baseColor", tempColor);
			}
		}
	}
}

void ATetrisBlockMesh::SetBlockShape(float inTileSize)
{
	//scale
	staticMeshComp1->SetRelativeScale3D(FVector(inTileSize / 100.0f));
	staticMeshComp2->SetRelativeScale3D(FVector(inTileSize / 100.0f));
	staticMeshComp3->SetRelativeScale3D(FVector(inTileSize / 100.0f));
	staticMeshComp4->SetRelativeScale3D(FVector(inTileSize / 100.0f));
	//rotate
	staticMeshComp1->SetWorldRotation(FRotator(90.0f,0.0f,0.0f));
	staticMeshComp2->SetWorldRotation(FRotator(90.0f,0.0f,0.0f));
	staticMeshComp3->SetWorldRotation(FRotator(90.0f,0.0f,0.0f));
	staticMeshComp4->SetWorldRotation(FRotator(90.0f,0.0f,0.0f));
	//position
	switch (currentBlock)
	{
	default:
	case ETetrisBlock::I:
		staticMeshComp1->SetRelativeLocation(FVector(0.0f, -inTileSize, 0.0f));
		staticMeshComp2->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		staticMeshComp3->SetRelativeLocation(FVector(0.0f, inTileSize, 0.0f));
		staticMeshComp4->SetRelativeLocation(FVector(0.0f, 2 * inTileSize, 0.0f));
		break;
	case ETetrisBlock::J:
		staticMeshComp1->SetRelativeLocation(FVector(0.0f, -inTileSize, inTileSize));
		staticMeshComp2->SetRelativeLocation(FVector(0.0f, -inTileSize, 0.0f));
		staticMeshComp3->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		staticMeshComp4->SetRelativeLocation(FVector(0.0f, inTileSize, 0.0f));
		break;
	case ETetrisBlock::L:
		staticMeshComp1->SetRelativeLocation(FVector(0.0f, -inTileSize, 0.0f));
		staticMeshComp2->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		staticMeshComp3->SetRelativeLocation(FVector(0.0f, inTileSize, 0.0f));
		staticMeshComp4->SetRelativeLocation(FVector(0.0f, inTileSize, inTileSize));
		break;
	case ETetrisBlock::O:
		staticMeshComp1->SetRelativeLocation(FVector(0.0f, 0.0f, inTileSize));
		staticMeshComp2->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		staticMeshComp3->SetRelativeLocation(FVector(0.0f, inTileSize, 0.0f));
		staticMeshComp4->SetRelativeLocation(FVector(0.0f, inTileSize, inTileSize));
		break;
	case ETetrisBlock::S:
		staticMeshComp1->SetRelativeLocation(FVector(0.0f, -inTileSize, 0.0f));
		staticMeshComp2->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		staticMeshComp3->SetRelativeLocation(FVector(0.0f, 0.0f, inTileSize));
		staticMeshComp4->SetRelativeLocation(FVector(0.0f, inTileSize, inTileSize));
		break;
	case ETetrisBlock::T:
		staticMeshComp1->SetRelativeLocation(FVector(0.0f, -inTileSize, 0.0f));
		staticMeshComp2->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		staticMeshComp3->SetRelativeLocation(FVector(0.0f, 0.0f, inTileSize));
		staticMeshComp4->SetRelativeLocation(FVector(0.0f, inTileSize, 0.0f));
		break;
	case ETetrisBlock::Z:
		staticMeshComp1->SetRelativeLocation(FVector(0.0f, -inTileSize, inTileSize));
		staticMeshComp2->SetRelativeLocation(FVector(0.0f, 0.0f, inTileSize));
		staticMeshComp3->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		staticMeshComp4->SetRelativeLocation(FVector(0.0f, inTileSize, 0.0f));
		break;
	}
}

void ATetrisBlockMesh::SetBlockActive(bool inactive)
{
	isActive = inactive;
}

void ATetrisBlockMesh::DropDownWithTime(float deltaTime)
{
	tempIntervalTime += deltaTime;
	if (tempIntervalTime>=0.5f)
	{
		if (BlockMeshMove(FVector2D(0, -1))==false)
		{
			if (tetrisGrid)
			{
				tetrisGrid->ReachTheGround();
			}
		}
		tempIntervalTime = 0.0f;
	}
}

bool ATetrisBlockMesh::BlockMeshMove(FVector2D inDirection)
{
	if (tetrisGrid)
	{
		TArray<FVector2D> currentIndexs = GetGridIndexs(FVector2D::ZeroVector);
		TArray<FVector2D> desiredIndexs = GetGridIndexs(inDirection);
		if (tetrisGrid->AreTheyValidIndex(desiredIndexs, currentIndexs))
		{
			AddActorWorldOffset(FVector(0.0f, inDirection.X * tetrisGrid->tileSize, inDirection.Y * tetrisGrid->tileSize));
			//remove block from grid
			tetrisGrid->tetrisGridMap.Add(currentIndexs[0], nullptr);
			tetrisGrid->tetrisGridMap.Add(currentIndexs[1], nullptr);
			tetrisGrid->tetrisGridMap.Add(currentIndexs[2], nullptr);
			tetrisGrid->tetrisGridMap.Add(currentIndexs[3], nullptr);
			//add block to grid
			tetrisGrid->tetrisGridMap.Add(desiredIndexs[0], staticMeshComp1);
			tetrisGrid->tetrisGridMap.Add(desiredIndexs[1], staticMeshComp2);
			tetrisGrid->tetrisGridMap.Add(desiredIndexs[2], staticMeshComp3);
			tetrisGrid->tetrisGridMap.Add(desiredIndexs[3], staticMeshComp4);
			return true;
		}
	}
	return false;
}

bool ATetrisBlockMesh::BlockMeshRotate(FRotator inRotation)
{
	FVector InitialLocation = GetActorLocation();
	FRotator InitialRotation = GetActorRotation();
	TArray<FVector2D> currentIndex = GetGridIndexs(FVector2D(0.0f));
	//rotate
	AddActorWorldRotation(inRotation);
	TArray<FVector2D> locationsToTry = { FVector2D(0.0f) };
	locationsToTry.Append({ FVector2D(1.0f,0.0f),FVector2D(-1.0f,0.0f) });
	if (currentBlock == ETetrisBlock::I)locationsToTry.Add(FVector2D(-2.0f, 0.0f));

	//check valid
	if (tetrisGrid)
	{
		for (FVector2D location:locationsToTry)
		{
			SetActorLocation(InitialLocation);
			AddActorWorldOffset(FVector(0.0f, location.X * tetrisGrid->tileSize, location.Y * tetrisGrid->tileSize));

			TArray<FVector2D> desiredIndex = GetGridIndexs(FVector2D(0.0f));
			if (tetrisGrid->AreTheyValidIndex(desiredIndex, currentIndex))
			{
				//remove block from grid
				tetrisGrid->tetrisGridMap.Add(currentIndex[0], nullptr);
				tetrisGrid->tetrisGridMap.Add(currentIndex[1], nullptr);
				tetrisGrid->tetrisGridMap.Add(currentIndex[2], nullptr);
				tetrisGrid->tetrisGridMap.Add(currentIndex[3], nullptr);
				//add block to grid
				tetrisGrid->tetrisGridMap.Add(desiredIndex[0], staticMeshComp1);
				tetrisGrid->tetrisGridMap.Add(desiredIndex[1], staticMeshComp2);
				tetrisGrid->tetrisGridMap.Add(desiredIndex[2], staticMeshComp3);
				tetrisGrid->tetrisGridMap.Add(desiredIndex[3], staticMeshComp4);
				//rotate
				staticMeshComp1->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));
				staticMeshComp2->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));
				staticMeshComp3->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));
				staticMeshComp4->SetWorldRotation(FRotator(90.0f, 0.0f, 0.0f));
				return true;
			}
		}
	}
	SetActorLocation(InitialLocation);
	SetActorRotation(InitialRotation);
	return false;
}

TArray<FVector2D> ATetrisBlockMesh::GetGridIndexs( FVector2D inOffset )
{
	if (tetrisGrid)
	{
		FVector2D mesh1Index = tetrisGrid->ConverWorldLocationToGridIndex(staticMeshComp1->GetComponentToWorld().GetLocation()) + inOffset;
		FVector2D mesh2Index = tetrisGrid->ConverWorldLocationToGridIndex(staticMeshComp2->GetComponentToWorld().GetLocation()) + inOffset;
		FVector2D mesh3Index = tetrisGrid->ConverWorldLocationToGridIndex(staticMeshComp3->GetComponentToWorld().GetLocation()) + inOffset;
		FVector2D mesh4Index = tetrisGrid->ConverWorldLocationToGridIndex(staticMeshComp4->GetComponentToWorld().GetLocation()) + inOffset;
		return { mesh1Index ,mesh2Index ,mesh3Index ,mesh4Index };
	}
	return TArray<FVector2D>();
}

void ATetrisBlockMesh::MoveSelfLeft()
{
	BlockMeshMove(FVector2D(-1.0f, 0.0f));
}

void ATetrisBlockMesh::MoveSelfRight()
{
	BlockMeshMove(FVector2D(1.0f, 0.0f));
}

void ATetrisBlockMesh::MoveSelfDown()
{
	if (BlockMeshMove(FVector2D(0.0f, -1.0f)))
		tempIntervalTime = 0.0f;
}

void ATetrisBlockMesh::HardDrop()
{
	while (BlockMeshMove(FVector2D(0.0f, -1.0f)))
		tempIntervalTime = 0.0f;
	if (tetrisGrid)
	{
		tetrisGrid->ReachTheGround();
	}
}

void ATetrisBlockMesh::RotateSelf()
{
	FRotator desiredRotation = FRotator(0.0f, 0.0f, 90.0f);
	if (currentBlock == ETetrisBlock::O) return;
	if (currentBlock==ETetrisBlock::I)
	{
		if (GetActorRotation().Equals(FRotator(0.0f), 5.0f))
		{
			desiredRotation = FRotator(0.0f, 0.0f, -90.0f);
		}
	}
	BlockMeshRotate(desiredRotation);
}

