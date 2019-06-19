// Fill out your copyright notice in the Description page of Project Settings.

#include "PIPlayerCharacter.h"
#include "PoppIt.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "PIDartProjectile.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

APIPlayerCharacter::APIPlayerCharacter()
: Super()
, HeldProjectile(nullptr)
, ProjectileHoldAnchor(nullptr)
{
	ProjectileHoldAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileHoldAnchor"));
	ProjectileHoldAnchor->SetupAttachment(GetMesh(), FName("RightHand"));
}

void APIPlayerCharacter::MoveForward(float Value)
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

void APIPlayerCharacter::MoveRight(float Value)
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

void APIPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APIPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APIPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("ThrowDart", IE_Pressed, this, &APIPlayerCharacter::BeginThrowDart);
}

void APIPlayerCharacter::GrabDart()
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

void APIPlayerCharacter::ReleaseDart()
{
	FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, false);
	if (HeldProjectile)
	{
		HeldProjectile->DetachFromActor(DetachmentTransformRules);
		if (GetFollowCamera())
		{
			const FVector ThrowDirection(GetActorForwardVector().X, GetActorForwardVector().Y, GetFollowCamera()->GetForwardVector().Z);
			HeldProjectile->LaunchInDirection(ThrowDirection);
		}
		HeldProjectile = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("APICharacter::ReleaseDart - HeldProjectile does not exist."));
	}
}

void APIPlayerCharacter::BeginThrowDart()
{
	OnBeginThrowDart.Broadcast();
}