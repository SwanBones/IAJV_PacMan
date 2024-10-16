// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../Public/Entity/AITasks"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FleePacman::UBTTask_FleePacman()
{
	NodeName = TEXT("Flee Pacman");

	// accept only vectors
	//BlackboardKey.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UBTTask_ChasePlayer, BlackboardKey));
}

EBTNodeResult::Type UBTTask_FleePacman::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Obtenez l'AIController et le fantôme contrôlé
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = Cast<APawn>(AIController->GetPawn());
	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	// Obtenez la position de Pac-Man
	APawn* Pacman = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Pacman)
	{
		return EBTNodeResult::Failed;
	}
	FVector PacmanPosition = Pacman->GetActorLocation();

	// Obtenez la position actuelle du fantôme
	FVector GhostPosition = AIPawn->GetActorLocation();

	// Calculez la direction opposée à Pac-Man
	FVector FleeDirection = GhostPosition - PacmanPosition;
	FleeDirection.Normalize();

	// Multipliez la direction par une distance pour obtenir une position éloignée
	const float FleeDistance = 500.0f;  // La distance à laquelle fuir
	FVector FleeTarget = GhostPosition + FleeDirection * FleeDistance;

	// Vérifiez si la position cible est navigable
	FNavLocation NavLocation;
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem && NavSystem->GetRandomPointInNavigableRadius(FleeTarget, 200.0f, NavLocation))
	{
		// Optionnel : Mettez à jour le Blackboard avec la nouvelle position
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, NavLocation.Location);

		// Signal the BehaviorTreeComponent that the task finished with a Success!
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	
		return EBTNodeResult::Succeeded;
	}

	// Si la position cible n'est pas navigable, échouez
	return EBTNodeResult::Failed;
}

FString UBTTask_FleePacman::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}