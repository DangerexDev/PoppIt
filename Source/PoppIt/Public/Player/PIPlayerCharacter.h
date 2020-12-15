// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PIPlayerCharacterBase.h"
#include "PIPlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginThrowDartSignature);

/**
 * 
 */
UCLASS()
class POPPIT_API APIPlayerCharacter : public APIPlayerCharacterBase
{
	GENERATED_BODY()

public:

	APIPlayerCharacter();

protected:

	class APIDartProjectile* HeldProjectile;

	// APIPlayerCharacterBase interface
	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	// End of APIPlayerCharacterBase interface

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

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

private:

	void BeginThrowDart();

#pragma endregion Dart

};
