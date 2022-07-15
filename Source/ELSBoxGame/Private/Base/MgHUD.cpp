#include "Base/MgHUD.h"
#include "Blueprint/UserWidget.h"
#include "Base/MgUserWidget.h"
#include "Base/MgGameMode.h"

void AMgHUD::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AMgGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode) 	ShowWidget(gameMode->currentGame);
}

void AMgHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMgHUD::ShowWidget(EMultiGames inGame)
{
	switch (inGame)
	{
	case EMultiGames::Game_None:
	default:
		break;
	case EMultiGames::Game_Multi:
		if (MgGameWidgetBP)
		{
			multiGameWidget = Cast<UMgUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), MgGameWidgetBP, FName("MultiGames")));
		}
		if (multiGameWidget)
		{
			multiGameWidget->AddToViewport();
			multiGameWidget->SetVisibility(ESlateVisibility::Visible);
		}
		if (pacManGameWidget) pacManGameWidget->SetVisibility(ESlateVisibility::Hidden);
		if (tetrisGameWidget) tetrisGameWidget->SetVisibility(ESlateVisibility::Hidden);
		break;

	case EMultiGames::Game_PacMan:
		if (PacManWidgetBP)
		{
			pacManGameWidget = Cast<UMgUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), PacManWidgetBP, FName("PacManGames")));
		}
		if (pacManGameWidget)
		{
			pacManGameWidget->AddToViewport();
			pacManGameWidget->SetVisibility(ESlateVisibility::Visible);
		}
		if (multiGameWidget) multiGameWidget->SetVisibility(ESlateVisibility::Hidden);
		if (tetrisGameWidget) tetrisGameWidget->SetVisibility(ESlateVisibility::Hidden);
		break;

	case EMultiGames::Game_Tetris:
		if (TetrisWidgetBP)
		{
			tetrisGameWidget = Cast<UMgUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), TetrisWidgetBP, FName("TetrisGames")));
		}
		if (tetrisGameWidget)
		{
			tetrisGameWidget->AddToViewport();
			tetrisGameWidget->SetVisibility(ESlateVisibility::Visible);
		}
		if (multiGameWidget) multiGameWidget->SetVisibility(ESlateVisibility::Hidden);
		if (pacManGameWidget) pacManGameWidget->SetVisibility(ESlateVisibility::Hidden);
		break;

	}

}
