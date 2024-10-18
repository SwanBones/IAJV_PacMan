// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PinkGhostChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_GROUPE5_API UBTTask_PinkGhostChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_PinkGhostChasePlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Description")
	float distance_ahead;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
