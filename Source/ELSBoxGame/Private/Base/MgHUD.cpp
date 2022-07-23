#include "Base/MgHUD.h"
#include "Blueprint/UserWidget.h"
#include "Base/MgUserWidget.h"
#include "Base/MgGameMode.h"
#include "Game/TetrisGrid.h"

void AMgHUD::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<AMgGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		ShowWidget(gameMode->currentGame, EMultiMenu::Menu_Main);
		gameMode->hud = this;
	}
}

void AMgHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMgHUD::ShowWidget(EMultiGames inGame, EMultiMenu inMenu)
{
	HideAllWidgets();
	CreateWidgetIfNeed(inGame);
	UMgUserWidget* tempWidget = nullptr;
	switch (inGame)
	{
	default:
	case EMultiGames::Game_None:
		break;
	case EMultiGames::Game_Multi:
		tempWidget = multiGameWidget;
		break;
	case EMultiGames::Game_Tetris:
		tempWidget = tetrisGameWidget;
		break;
	case EMultiGames::Game_PacMan:
		tempWidget = pacManGameWidget;
		break;
	}
	if (tempWidget)
	{
		tempWidget->SetVisibility(ESlateVisibility::Visible);
		tempWidget->ShowInMenu(inMenu);
		currentMenu = inMenu;
	}
}

void AMgHUD::ButtonClicked(EMultiButton inButton)
{
	if (gameMode)
	{
		switch (inButton)
		{
		case EMultiButton::Button_MainMenu:
			if (currentMenu != EMultiMenu::Menu_Main)
			{
				ShowWidget(gameMode->currentGame, EMultiMenu::Menu_Main);
			}
			else
			{
				ShowWidget(EMultiGames::Game_Multi, EMultiMenu::Menu_Main);
			}
			break;
		case EMultiButton::Button_Play:
			ShowWidget(gameMode->currentGame, EMultiMenu::Menu_Game);
			gameMode->PlayCurrentGame();
			break;
		case EMultiButton::Button_Pause:
			ShowWidget(gameMode->currentGame, EMultiMenu::Menu_Pause);
			break;
		case EMultiButton::Button_Options:
			ShowWidget(gameMode->currentGame, EMultiMenu::Menu_Options);
			break;
		case EMultiButton::Button_LeaderBoard:
			ShowWidget(gameMode->currentGame, EMultiMenu::Menu_LeaderBoard);
			break;
		default:
			break;
		}
	}
}

void AMgHUD::CreateWidgetIfNeed(EMultiGames inGame)
{
	switch (inGame)
	{
	case EMultiGames::Game_None:
	default:
		break;
	case EMultiGames::Game_Multi:
		if (multiGameWidget==nullptr)
		{
			if (MgGameWidgetBP)
			{
				multiGameWidget = Cast<UMgUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), MgGameWidgetBP, FName("MultiGames")));
			}
			if (multiGameWidget)		multiGameWidget->AddToViewport();
		}
		break;

	case EMultiGames::Game_PacMan:
		if (pacManGameWidget==nullptr)
		{
			if (PacManWidgetBP)
			{
				pacManGameWidget = Cast<UMgUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), PacManWidgetBP, FName("PacManGames")));
			}
			if (pacManGameWidget)		pacManGameWidget->AddToViewport();
		}
		break;

	case EMultiGames::Game_Tetris:
		if (tetrisGameWidget==nullptr)
		{
			if (TetrisWidgetBP)
			{
				tetrisGameWidget = Cast<UMgUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), TetrisWidgetBP, FName("TetrisGames")));
			}
			if (tetrisGameWidget)		tetrisGameWidget->AddToViewport();
		}
		break;
	}
}

void AMgHUD::HideAllWidgets()
{
	if (multiGameWidget)		multiGameWidget->SetVisibility(ESlateVisibility::Hidden);
	if (tetrisGameWidget)		tetrisGameWidget->SetVisibility(ESlateVisibility::Hidden);
	if (pacManGameWidget)		pacManGameWidget->SetVisibility(ESlateVisibility::Hidden);
}
