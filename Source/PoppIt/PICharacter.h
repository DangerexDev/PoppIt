// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoppItCharacter.h"
#include "PICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginThrowDartSignature);

/**
 * 
 */
UCLASS()
class POPPIT_API APICharacter : public APoppItCharacter
{
	GENERATED_BODY()

public:

	APICharacter();

#pragma region Dart

public:

	/** Broadcasts whenever the throw dart keybinding is pressed */
	UPROPERTY(BlueprintAssignable, Category = "Dart")
	FBeginThrowDartSignature OnBeginThrowDart;


	/** The anchor point on the character's hand where the dart attaches */
	UPROPERTY(EditDefaultsOnly, Category = "Dart")
	class USceneComponent* ProjectileHoldAnchor;
	

	/** The dart type that should be spawned on a call to GrabDart */
	UPROPERTY(EditAnywhere, Category = "Dart")
	class TSubclassOf<class APIDartProjectile> DartType;


	/** Spawn a dart and attach it to ProjectileHoldAnchor */
	UFUNCTION(BlueprintCallable, Category = "Dart")
	void GrabDart();

	/** Launch the currently held dart */
	UFUNCTION(BlueprintCallable, Category = "Dart")
	void ReleaseDart();

protected:

	class APIDartProjectile* HeldProjectile;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

private:

	void BeginThrowDart();

#pragma endregion Dart

};
