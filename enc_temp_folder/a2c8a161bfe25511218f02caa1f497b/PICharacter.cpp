// Fill out your copyright notice in the Description page of Project Settings.

#include "PICharacter.h"
#include "GameFramework/Actor.h"
#include "PIDartProjectile.h"

APICharacter::APICharacter()
: Super()
, HeldProjectile(nullptr)
{
}

void APICharacter::ReleaseDart()
{
	FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, false);
	HeldProjectile->DetachFromActor(DetachmentTransformRules);
	HeldProjectile->LaunchInDirection(GetActorForwardVector());
	HeldProjectile = nullptr;
}

void APICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ThrowDart", IE_Pressed, this, &APICharacter::BeginThrowDart);
}

void APICharacter::BeginThrowDart()
{
	OnBeginThrowDart.Broadcast();
}