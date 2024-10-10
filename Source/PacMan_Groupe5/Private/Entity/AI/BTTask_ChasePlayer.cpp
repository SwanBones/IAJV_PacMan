// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AI/BTTask_ChasePlayer.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Entity/PacManPlayer.h"
#include "Kismet/GameplayStatics.h"

class APacManPlayer;

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
	NodeName = TEXT("Find Pacman");

	distance_ahead = 1000.0f;

	// accept only vectors
	BlackboardKey.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UBTTask_ChasePlayer, BlackboardKey));
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	// Get AI Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* AIPawn {AIController->GetPawn()};
	APawn* Pacman = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	// Get Pawn Origin
	const FVector Origin {Pacman->GetActorLocation()};
	// Get direction wich Pacman is going to
	const FVector PacmanDirection = Cast<APacManPlayer>(Pacman)->CurrentDirection;
	
	// const float distance_ahead = 200.0f;
	
	// Calculate a point in front of the Pacman
	FVector TargetPosition = Origin + (PacmanDirection * distance_ahead);

	// Obtain the Navigation System and find a random location
	const UNavigationSystemV1* NavSystem {UNavigationSystemV1::GetCurrent(GetWorld())};
	if(IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(TargetPosition, 0.0, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	// Signal the BehaviorTreeComponent that the task finished with a Success!
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	
	return EBTNodeResult::Succeeded;
}

FString UBTTask_ChasePlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}