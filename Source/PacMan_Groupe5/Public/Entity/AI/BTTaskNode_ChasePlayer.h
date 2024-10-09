// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_GROUPE5_API UBTTaskNode_ChasePlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_ChasePlayer();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PlayerKey;

	

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	//virtual FString GetStaticDescription() const override;

	UNavigationSystemV1* NavArea;
};
