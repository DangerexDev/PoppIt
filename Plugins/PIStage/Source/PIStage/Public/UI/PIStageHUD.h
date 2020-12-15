#pragma once

#include "UI/PIHUDBase.h"
#include "PIStageHUD.generated.h"

UCLASS()
class PISTAGE_API APIStageHUD : public APIHUDBase
{
	GENERATED_BODY()
	
public:

	APIStageHUD();
	//virtual ~APIStageHUD() {}

	virtual void SetPauseMenuVisible(const bool bInVisible);
};
