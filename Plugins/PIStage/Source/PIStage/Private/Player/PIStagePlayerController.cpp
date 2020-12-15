#include "Player/PIStagePlayerController.h"

#include "UI/PIStageHUD.h"

APIStagePlayerController::APIStagePlayerController()
	: Super()
{
}

void APIStagePlayerController::TogglePause()
{
	SetPause(!IsPaused());

	if (APIStageHUD* const HUD = GetHUD<APIStageHUD>())
	{
		HUD->SetPauseMenuVisible(IsPaused());
	}
}

void APIStagePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Pause", IE_Pressed, this, &ThisClass::TogglePause);
}

