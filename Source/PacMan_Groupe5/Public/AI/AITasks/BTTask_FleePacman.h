// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FleePacman.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_GROUPE5_API UBTTask_FleePacman : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FleePacman();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	float FleeDistance = 500.0f; 

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	FVector FindFurthestPointOnNavMesh(const FVector& PacManLocation) const;
	virtual FString GetStaticDescription() const override;
};
