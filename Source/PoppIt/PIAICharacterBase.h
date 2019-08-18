// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PICharacterBase.h"
#include "PIAICharacterBase.generated.h"

UCLASS()
class POPPIT_API APIAICharacterBase : public APICharacterBase
{
	GENERATED_BODY()
	
public:
	APIAICharacterBase();

protected:
	virtual void BeginPlay() override;
};
