// Fill out your copyright notice in the Description page of Project Settings.

#include "PIAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "TimerManager.h"
#include "BehaviorTree/BlackboardComponent.h"


APIAIController::APIAIController()
	: Super()
	, BehaviorTree(nullptr)
	, OpponentActorTag("Player")
	, LineOfSightBrokenStopChasingOpponentWaitDuration(4.0f)
	, HasLineOfSightBlackboardKeyName("bHasLineOfSight")
	, OpponentActorBlackboardKeyName("OpponentActor")
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

void APIAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &APIAIController::OnTargetPerceptionUpdated);
	}
}

void APIAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UWorld* const World = GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();
		if (Actor && Actor->ActorHasTag(OpponentActorTag) && Stimulus.WasSuccessfullySensed())
		{
			TimerManager.ClearTimer(StopChasingOpponentTimerHandle);
			Blackboard->SetValueAsBool(HasLineOfSightBlackboardKeyName, true);
			Blackboard->SetValueAsObject(OpponentActorBlackboardKeyName, Actor);
		}
		else
		{
			TimerManager.SetTimer(StopChasingOpponentTimerHandle, this, &APIAIController::StopChasingOpponent, LineOfSightBrokenStopChasingOpponentWaitDuration, false);
		}
	}
}

void APIAIController::StopChasingOpponent()
{
	Blackboard->SetValueAsBool(HasLineOfSightBlackboardKeyName, false);
	Blackboard->SetValueAsObject(OpponentActorBlackboardKeyName, nullptr);
}
