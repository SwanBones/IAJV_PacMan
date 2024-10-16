// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/PacEntity.h"
#include "Ghost.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_GROUPE5_API AGhost : public APacEntity
{
	GENERATED_BODY()

public:
	// Constructor
	AGhost();

	// Public attribute
	// BaseFlipbook
	// DeadFlipbook
	// FrightenFlipbook
	bool IsDead;
	bool IsFrightened;

	// Public methods
	void SetAliveMode();
	void SetDeadMode();
	void SetFrightenMode();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// UFUNCTION()
	// void OnOverlap(AActor* MyActor, AActor* OtherActor);
	
};
