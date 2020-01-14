// Fill out your copyright notice in the Description page of Project Settings.


#include "PIBTTask_ChasePlayer.h"
#include "PIAICharacterBase.h"
#include "AIController.h"

UPIBTTask_ChasePlayer::UPIBTTask_ChasePlayer(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, ChaseSpeed(500.0f)
	, AIOwner(nullptr)
{
}

EBTNodeResult::Type UPIBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!AIOwner)
	{
		AIOwner = Cast<AAIController>(OwnerComp.GetOuter());
	}

	if (AIOwner)
	{
		if (APIAICharacterBase* const ControlledPawn = Cast<APIAICharacterBase>(AIOwner->GetPawn()))
		{
			ControlledPawn->SetWalkSpeed(ChaseSpeed);
			FinishExecute(true);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

void UPIBTTask_ChasePlayer::FinishExecute(bool bSuccess)
{
	UBehaviorTreeComponent* const OwnerComp = Cast<UBehaviorTreeComponent>(GetOuter());
	EBTNodeResult::Type NodeResult(bSuccess ? EBTNodeResult::Succeeded : EBTNodeResult::Failed);

	if (OwnerComp)
	{
		FinishLatentTask(*OwnerComp, NodeResult);
	}
}