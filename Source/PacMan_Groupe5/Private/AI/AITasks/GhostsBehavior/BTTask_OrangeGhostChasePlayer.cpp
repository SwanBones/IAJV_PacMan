// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AITasks/GhostsBehavior/BTTask_OrgangeGhostChasePlayer.h"

#include "AIController.h"
#include <msctf.h>
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_OrgangeGhostChasePlayer::UBTTask_OrgangeGhostChasePlayer()
{
	NodeName = TEXT("Orange Ghost Chase Player");

	// accept only vectors
	BlackboardKey.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UBTTask_OrgangeGhostChasePlayer, BlackboardKey));
}

EBTNodeResult::Type UBTTask_OrgangeGhostChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	// Get AI Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* AIPawn {AIController->GetPawn()};

	// Get Pawn Origin
	const FVector Origin {AIPawn->GetActorLocation()};

	// Obtain the Navigation System and find a random location
	const UNavigationSystemV1* NavSystem {UNavigationSystemV1::GetCurrent(GetWorld())};
	if(IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	// Signal the BehaviorTreeComponent that the task finished with a Success!
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	
	return EBTNodeResult::Succeeded;
}

FString UBTTask_OrgangeGhostChasePlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
