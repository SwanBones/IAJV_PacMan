// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/GhostAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Entity/Ghost.h"

AGhostAIController::AGhostAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
}

void AGhostAIController::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
}

void AGhostAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
	}
}

/*void AGhostAIController::OnMoveCompleted(const FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	// Récupère le Pawn (le fantôme) contrôlé par ce contrôleur AI
	if (APawn* ControlledPawn = GetPawn())
	{
		// Cast le Pawn en AGhost pour accéder à ses méthodes et propriétés
		AGhost* MyGhost = Cast<AGhost>(ControlledPawn);
		if (MyGhost && MyGhost->IsDead)
		{
			// Le fantôme est mort et vient de terminer son mouvement vers le point de respawn
			MyGhost->SetAliveMode();  // Remettre le fantôme en mode "Alive"
		}
	}
}*/