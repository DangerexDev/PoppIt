// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PIBTTask_ChasePlayer.generated.h"


UCLASS()
class POPPIT_API UPIBTTask_ChasePlayer : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()
	
	
	// Begin UBTTaskNode Interface
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// End UBTTaskNode Interface


public:

	UPROPERTY(EditAnywhere)
	float ChaseSpeed;


protected:

	/** Cached AIController owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	class AAIController* AIOwner;

	/** finishes task execution with Success or Fail result */
	void FinishExecute(bool bSuccess);

};
