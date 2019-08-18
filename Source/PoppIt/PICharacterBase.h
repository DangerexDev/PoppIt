// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PICharacterBase.generated.h"

UCLASS()
class POPPIT_API APICharacterBase : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Damage, meta = (AllowPrivateAccess = "true"))
	class UPIDamageableComponent* DamageableComponent;
	
public:
	APICharacterBase();

protected:
	virtual void BeginPlay() override;
};
