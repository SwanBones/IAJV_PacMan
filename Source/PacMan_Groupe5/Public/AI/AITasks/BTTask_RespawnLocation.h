// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RespawnLocation.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_GROUPE5_API UBTTask_RespawnLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RespawnLocation();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	//virtual FString GetStaticDescription() const override;
};
