// Fill out your copyright notice in the Description page of Project Settings.

#include "PIDamageableComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPIDamageableComponent::UPIDamageableComponent()
	: MaxHealth(10.0f)
	, CurrentHealth(0.0f)
{
}

void UPIDamageableComponent::ApplyDamage(const float InDamage)
{
	CurrentHealth = FMath::Max(0.0f, CurrentHealth - InDamage);
	if (CurrentHealth == 0.0f)
	{
		GetOwner()->Destroy();
	}
}

// Called when the game starts
void UPIDamageableComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

