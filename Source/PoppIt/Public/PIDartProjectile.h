// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PIDartProjectile.generated.h"

UCLASS()
class POPPIT_API APIDartProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	APIDartProjectile();

protected:
	virtual void BeginPlay() override;

public:
	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectlle)
	class USphereComponent* CollisionComponent;

	// Projectile movement component
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	// Static mesh component
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	float BaseDamage;

	// Function that initializes the projectile's velocity in the launch direction
	void LaunchInDirection(const FVector& LaunchDirection);

	// Function that is called when the projectile hits something
	UFUNCTION()
	void OnStop(const FHitResult& ImpactResult);
};
