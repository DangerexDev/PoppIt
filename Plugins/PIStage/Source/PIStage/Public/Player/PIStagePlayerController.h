#pragma once

#include "CoreMinimal.h"
#include "Player/PIPlayerControllerBase.h"
#include "PIStagePlayerController.generated.h"

UCLASS()
class PISTAGE_API APIStagePlayerController : public APIPlayerControllerBase
{
	GENERATED_BODY()

public:

	APIStagePlayerController();

	UFUNCTION(BlueprintCallable, Category = Pause)
	void TogglePause();

protected:

	//~ Begin APlayerController Interface
	virtual void SetupInputComponent() override;
	//~ End APlayerController Interface
};
