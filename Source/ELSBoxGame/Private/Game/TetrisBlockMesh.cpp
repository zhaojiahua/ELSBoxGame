#include "Game/TetrisBlockMesh.h"
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

