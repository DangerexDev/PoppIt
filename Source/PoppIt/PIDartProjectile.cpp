// Fill out your copyright notice in the Description page of Project Settings.

#include "PIDartProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

APIDartProjectile::APIDartProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &APIDartProjectile::OnHit);

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

// Function that is called when the projectile hits something
void APIDartProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		//OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}