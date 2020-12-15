// Fill out your copyright notice in the Description page of Project Settings.

#include "PIDartProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PIDamageableComponent.h"
#include "Components/StaticMeshComponent.h"

APIDartProjectile::APIDartProjectile()
	: BaseDamage(1.0f)
{
	// Use a sphere as a simple collision representation
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	// Set the sphere's collision radius
	CollisionComponent->InitSphereRadius(15.0f);
	// Set the root component to be the collision component
	RootComponent = CollisionComponent;

	// Use this component to drive this projectile's movement
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
	ProjectileMovementComponent->MaxSpeed = 2000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->bSimulationEnabled = false;
	ProjectileMovementComponent->OnProjectileStop.AddDynamic(this, &APIDartProjectile::OnStop);

	// Create an empty mesh component that has its mesh defined in the editor on Blueprint subclasses
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetRelativeLocation(FVector::ZeroVector);

	// Die after 3 seconds
	InitialLifeSpan = 3.0f;
}

void APIDartProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Function that initializes the projectile's velocity in the launch direction
void APIDartProjectile::LaunchInDirection(const FVector& LaunchDirection)
{
	ProjectileMovementComponent->Velocity = LaunchDirection * ProjectileMovementComponent->InitialSpeed;
	ProjectileMovementComponent->bSimulationEnabled = true;
}

void APIDartProjectile::OnStop(const FHitResult& ImpactResult)
{
	if (ImpactResult.Actor.IsValid())
	{
		if (UPIDamageableComponent* DamageableComponent = ImpactResult.Actor->FindComponentByClass<UPIDamageableComponent>())
		{
			DamageableComponent->ApplyDamage(BaseDamage);
			Destroy();
		}
	}
}
