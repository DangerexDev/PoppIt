// Fill out your copyright notice in the Description page of Project Settings.

#include "PICharacter.h"
#include "GameFramework/Actor.h"

void APICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ThrowDart", IE_Pressed, this, &APICharacter::ThrowDart);
}

void APICharacter::ThrowDart()
{
	OnThrowDart.Broadcast();
}
