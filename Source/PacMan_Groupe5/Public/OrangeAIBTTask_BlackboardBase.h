// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "OrangeAIBTTask_BlackboardBase.generated.h"

/**
 * BTTask (BehaviorTree Task) for a random location on the navmesh
 */
UCLASS()
class PACMAN_GROUPE5_API UOrangeAIBTTask_BlackboardBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UOrangeAIBTTask_BlackboardBase();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = true))
	float searchRadius{ 5000.f };
};
