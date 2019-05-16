// Fill out your copyright notice in the Description page of Project Settings.

#include "PICharacter.h"
#include "PoppIt.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "PIDartProjectile.h"
#include "Components/InputComponent.h"

APICharacter::APICharacter()
: Super()
, ProjectileHoldAnchor(nullptr)
, HeldProjectile(nullptr)
{
	ProjectileHoldAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileHoldAnchor"));
	ProjectileHoldAnchor->SetupAttachment(GetMesh(), FName("RightHand"));
}

void APICharacter::GrabDart()
{
	HeldProjectile = GetWorld()->SpawnActor<APIDartProjectile>(DartType, ProjectileHoldAnchor->GetComponentLocation(), ProjectileHoldAnchor->GetComponentRotation());
	if (HeldProjectile)
	{
		HeldProjectile->AttachToComponent(ProjectileHoldAnchor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
	else
	{
		UE_LOG(LogPoppIt, Error, TEXT("APICharacter::GrabDart - HeldProjectile cannot be spawned. Make sure DartType is set to a valid class."));
	}
}

void APICharacter::ReleaseDart()
{
	FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, false);
	if (HeldProjectile)
	{
		HeldProjectile->DetachFromActor(DetachmentTransformRules);
		HeldProjectile->LaunchInDirection(GetActorForwardVector());
		HeldProjectile = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("APICharacter::ReleaseDart - HeldProjectile does not exist."));
	}
}

void APICharacter::MoveForward(float Value)
{
	if (GetVelocity().IsZero() && Value == 0)
	{
		bUseControllerRotationYaw = false;
	}
	else
	{
		bUseControllerRotationYaw = true;
	}

	Super::MoveForward(Value);
}

void APICharacter::MoveRight(float Value)
{
	if (GetVelocity().IsZero() && Value == 0)
	{
		bUseControllerRotationYaw = false;
	}
	else
	{
		bUseControllerRotationYaw = true;
	}

	Super::MoveRight(Value);
}

void APICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APICharacter::MoveRight);

	PlayerInputComponent->BindAction("ThrowDart", IE_Pressed, this, &APICharacter::BeginThrowDart);
}

void APICharacter::BeginThrowDart()
{
	OnBeginThrowDart.Broadcast();
}