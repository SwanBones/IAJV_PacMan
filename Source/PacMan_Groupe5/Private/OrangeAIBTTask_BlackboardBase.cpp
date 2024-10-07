// Fill out your copyright notice in the Description page of Project Settings.


#include "OrangeAIBTTask_BlackboardBase.h"
#include "AIController.h"         // For AAIController
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"



UOrangeAIBTTask_BlackboardBase::UOrangeAIBTTask_BlackboardBase()
{
	NodeName = TEXT("Find Random Location");
	//accept only vectors
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UOrangeAIBTTask_BlackboardBase, BlackboardKey));
}

EBTNodeResult::Type UOrangeAIBTTask_BlackboardBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};
	AAIController* AIController { OwnerComp.GetAIOwner() };
	
	//getAIPawn
	const APawn* AIPawn { AIController->GetPawn() };
	//get pawn origin
	const FVector Origin { AIPawn->GetActorLocation() };
	//optain navigation system and find a random location
	const UNavigationSystemV1* NavSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };
	if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, searchRadius, Location) )
	{//location = where we want to store the information
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName,Location.Location);
	}
	//signal the behaviorTreeComponent that the task finished with a success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

FString UOrangeAIBTTask_BlackboardBase::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
