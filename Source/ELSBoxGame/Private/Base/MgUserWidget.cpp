
#include "Base/MgUserWidget.h"
#include "Base/MgGameMode.h"
#include "Base/MgHUD.h"

void UMgUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	gameMode = Cast<AMgGameMode>(GetWorld()->GetAuthGameMode());
	
}

void UMgUserWidget::ShowInMenu_Implementation(EMultiMenu inMenu)
{
}

void UMgUserWidget::ButtonClicked(EMultiButton inButton)
{
	if (gameMode)
	{
		if (gameMode->hud)
		{
			gameMode->hud->ButtonClicked(inButton);
		}
	}
}

void UMgUserWidget::UpdataLevel(int inlevel)
{

}

void UMgUserWidget::UpdataPoints(int inpoints)
{

}

void UMgUserWidget::UpdataCombo(int incombo)
{

}

void UMgUserWidget::UpdataProgression(float inprogress)
{

}
