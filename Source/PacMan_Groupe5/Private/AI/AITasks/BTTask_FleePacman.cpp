// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AITasks/BTTask_FleePacman.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Entity/PacManPlayer.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FleePacman::UBTTask_FleePacman()
{
	NodeName = TEXT("Find Flee Pacman Location");

	// accept only vectors
	BlackboardKey.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UBTTask_FleePacman, BlackboardKey));
}

EBTNodeResult::Type UBTTask_FleePacman::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// // Obtenez l'AIController et le fantôme contrôlé
	// AAIController* AIController = OwnerComp.GetAIOwner();
	// APawn* AIPawn = Cast<APawn>(AIController->GetPawn());
	// if (!AIPawn)
	// {
	// 	return EBTNodeResult::Failed;
	// }
	//
	// // Obtenez la position de Pac-Man
	// APawn* Pacman = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	// if (!Pacman)
	// {
	// 	return EBTNodeResult::Failed;
	// }
	// FVector PacmanPosition = Pacman->GetActorLocation();
	//
	// // Obtenez la position actuelle du fantôme
	// FVector GhostPosition = AIPawn->GetActorLocation();
	//
	// // Calculez la direction opposée à Pac-Man
	// FVector FleeDirection = GhostPosition - PacmanPosition;
	// FleeDirection.Normalize();
	//
	// // Multipliez la direction par une distance pour obtenir une position éloignée
	// FVector FleeTarget = GhostPosition + FleeDirection * FleeDistance;
	//
	// // Vérifiez si la position cible est navigable
	// FNavLocation NavLocation;
	// const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	// if (NavSystem && NavSystem->GetRandomPointInNavigableRadius(FleeTarget, 1.0f, NavLocation))
	// {
	// 	// Optionnel : Mettez à jour le Blackboard avec la nouvelle position
	// 	AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, NavLocation.Location);
	//
	// 	// Signal the BehaviorTreeComponent that the task finished with a Success!
	// 	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	
	// 	return EBTNodeResult::Succeeded;
	// }
	//
	// // Si la position cible n'est pas navigable, échouez
	// return EBTNodeResult::Failed;

	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!AIController || !BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	// Récupérer la position du fantôme et de Pac-Man
	FVector GhostLocation = AIController->GetPawn()->GetActorLocation();
	FVector PacManLocation = FVector::ZeroVector;

	APacManPlayer* PacMan = Cast<APacManPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PacMan)
	{
		PacManLocation = PacMan->GetActorLocation();
	}

	// Trouver le point le plus éloigné sur le NavMesh par rapport à Pac-Man
	FVector FleeLocation = FindFurthestPointOnNavMesh(PacManLocation);

	if (FleeLocation != FVector::ZeroVector)
	{
		//BlackboardComp->SetValueAsVector("MoveToLocation", FleeLocation);
		BlackboardComp->SetValueAsVector(BlackboardKey.SelectedKeyName, FleeLocation);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

// Fonction pour trouver le point le plus éloigné du Pac-Man sur le NavMesh
FVector UBTTask_FleePacman::FindFurthestPointOnNavMesh(const FVector& PacManLocation) const
{
	// Récupérer le système de navigation
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSystem)
	{
		return FVector::ZeroVector;
	}

	// Variables pour stocker les résultats de la recherche du point
	FNavLocation FleeLocation;

	// Chercher un point éloigné à partir de Pac-Man, ici avec un rayon très grand (par exemple 10000 unités)
	float SearchRadius = 10000.0f;

	// Chercher un point dans un grand rayon autour de Pac-Man
	if (NavSystem->GetRandomPointInNavigableRadius(PacManLocation, SearchRadius, FleeLocation))
	{
		return FleeLocation.Location;
	}

	// Si aucun point n'a été trouvé, retourner un vecteur nul
	return FVector::ZeroVector;
}

FString UBTTask_FleePacman::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}