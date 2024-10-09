// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AI/BTTaskNode_ChasePlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTaskNode_ChasePlayer::UBTTaskNode_ChasePlayer()
{
	NodeName = "Find Pacman";
}

EBTNodeResult::Type UBTTaskNode_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};
	
	NavArea = UNavigationSystemV1::GetCurrent(GetWorld());
	APawn* Pacman = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if(IsValid(NavArea) && NavArea->GetRandomPointInNavigableRadius(Pacman->GetActorLocation(), 5.0, Location))
	{
		auto Blackboard = OwnerComp.GetBlackboardComponent();
		//Blackboard->SetValueAsObject(PlayerKey.SelectedKeyName, Location);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
}



