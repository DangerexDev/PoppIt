#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PIPlayerControllerBase.generated.h"

UCLASS()
class POPPIT_API APIPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:

	APIPlayerControllerBase();
};