// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "PIAIController.generated.h"


UCLASS()
class POPPIT_API APIAIController : public AAIController
{
	GENERATED_BODY()
	
	APIAIController();
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Perception, meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* AIPerception;
	
	
public:

	UPROPERTY(EditAnywhere, Category = BehaviorTree)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = Chase)
	FName OpponentActorTag;

	UPROPERTY(EditAnywhere, Category = Chase)
	float LineOfSightBrokenStopChasingOpponentWaitDuration;

	UPROPERTY(EditAnywhere, Category = Chase)
	FName HasLineOfSightBlackboardKeyName;
	
	UPROPERTY(EditAnywhere, Category = Chase)
	FName OpponentActorBlackboardKeyName;

	UPROPERTY(EditAnywhere, Category = Patrol)
	FName PatrolOriginBlackboardKeyName;

protected:

	void UpdatePatrolOriginLocation(const APawn* const InPawn);


	// Begin AController Interface
	virtual void OnPossess(APawn* InPawn) override;
	// End AController Interface

private:

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void StopChasingOpponent();

	FTimerHandle StopChasingOpponentTimerHandle;

};
