// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AITasks/BTTask_RespawnLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RespawnLocation::UBTTask_RespawnLocation()
{
	NodeName = TEXT("Find Respawn Location");
}

EBTNodeResult::Type UBTTask_RespawnLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	// Get AI Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* AIPawn {AIController->GetPawn()};

	FVector TargetPosition = {-10.0,-110.0,-180.0};

	// Obtain the Navigation System and find a random location
	const UNavigationSystemV1* NavSystem {UNavigationSystemV1::GetCurrent(GetWorld())};
	if(IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(TargetPosition, 75.0, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector("TargetLocation", Location.Location);
	}

	// Signal the BehaviorTreeComponent that the task finished with a Success!
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	
	return EBTNodeResult::Succeeded;
}

