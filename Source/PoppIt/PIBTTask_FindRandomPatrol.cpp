// Fill out your copyright notice in the Description page of Project Settings.

#include "PIBTTask_FindRandomPatrol.h"
#include "PIAICharacterBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"


UPIBTTask_FindRandomPatrol::UPIBTTask_FindRandomPatrol(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, PatrolSpeed(125.0f)
	, PatrolRadius(1000.0f)
	, AIOwner(nullptr)
{
}

EBTNodeResult::Type UPIBTTask_FindRandomPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!AIOwner)
	{
		AIOwner = Cast<AAIController>(OwnerComp.GetOuter());
	}

	if (AIOwner)
	{
		if (APIAICharacterBase* const ControlledPawn = Cast<APIAICharacterBase>(AIOwner->GetPawn()))
		{
			ControlledPawn->SetWalkSpeed(PatrolSpeed);
			
			if (UBlackboardComponent* const BlackboardComp = OwnerComp.GetBlackboardComponent())
			{
				const FVector PatrolOrigin = BlackboardComp->GetValueAsVector(GetSelectedBlackboardKey());
				FNavLocation PatrolNavLocation;
				FVector PatrolLocation = PatrolOrigin;

				if (UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetNavigationSystem(this))
				{
					if (const bool bSuccess = NavigationSystem->GetRandomReachablePointInRadius(PatrolOrigin, PatrolRadius, PatrolNavLocation))
					{
						PatrolLocation = PatrolNavLocation.Location;
					}
				}

				BlackboardComp->SetValueAsVector(GetPatrolDestinationBlackboardKey(), PatrolLocation);
			}

			FinishExecute(true);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

void UPIBTTask_FindRandomPatrol::FinishExecute(bool bSuccess)
{
	if (UBehaviorTreeComponent* const OwnerComp = Cast<UBehaviorTreeComponent>(GetOuter()))
	{
		EBTNodeResult::Type NodeResult(bSuccess ? EBTNodeResult::Succeeded : EBTNodeResult::Failed);
		FinishLatentTask(*OwnerComp, NodeResult);
	}
}