// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PIBTTask_FindRandomPatrol.generated.h"


UCLASS()
class POPPIT_API UPIBTTask_FindRandomPatrol : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()
	
	
	/** get name of selected blackboard key */
	FName GetPatrolDestinationBlackboardKey() const;
	

	// Begin UBTTaskNode Interface
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// End UBTTaskNode Interface


public:

	UPROPERTY(EditAnywhere)
	float PatrolSpeed;

	UPROPERTY(EditAnywhere)
	float PatrolRadius;
	
protected:

	/** Blackboard key selector */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector PatrolDestinationBlackboardKey;

	/** Cached AIController owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	class AAIController* AIOwner;

	/** finishes task execution with Success or Fail result */
	void FinishExecute(bool bSuccess);
};

//////////////////////////////////////////////////////////////////////////
// Inlines

FORCEINLINE FName UPIBTTask_FindRandomPatrol::GetPatrolDestinationBlackboardKey() const
{
	return PatrolDestinationBlackboardKey.SelectedKeyName;
}
