// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PIDamageableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POPPIT_API UPIDamageableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPIDamageableComponent();

	UFUNCTION()
	void ApplyDamage(const float InDamage);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health)
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = CurrentHealth)
	float CurrentHealth;

	// Called when the game starts
	virtual void BeginPlay() override;
	
};
