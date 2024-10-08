// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PacEntity.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Pawn.h"
#include "PacManPlayer.generated.h"

UCLASS()
class PACMAN_GROUPE5_API APacManPlayer : public APacEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APacManPlayer();

	//int Score;

	FVector CurrentDirection = FVector(1.0f, 0.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FlipbookUp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FlipbookDown;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FlipbookLeft;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FlipbookRight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUpDown(float value);

	void MoveLeftRight(float value);

};
