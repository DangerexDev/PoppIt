// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoppItCharacter.h"
#include "PICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FThrowDartSignature);

/**
 * 
 */
UCLASS()
class POPPIT_API APICharacter : public APoppItCharacter
{
	GENERATED_BODY()

public:
	/** Broadcasts whenever the throw dart keybinding is pressed */
	UPROPERTY(BlueprintAssignable)
	FThrowDartSignature OnThrowDart;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

private:
	void ThrowDart();
};
