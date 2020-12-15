// Fill out your copyright notice in the Description page of Project Settings.

#include "PICharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "PIDamageableComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


APICharacterBase::APICharacterBase()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	DamageableComponent = CreateDefaultSubobject<UPIDamageableComponent>(TEXT("DamageableComponent"));
}

void APICharacterBase::SetWalkSpeed(const float InWalkSpeed)
{
	if (UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement())
	{
		CharacterMovementComponent->MaxWalkSpeed = InWalkSpeed;
	}
}

void APICharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
