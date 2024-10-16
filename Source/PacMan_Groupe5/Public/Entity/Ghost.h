// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UPaperFlipbook* BaseFlipbookUp;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UPaperFlipbook* BaseFlipbookDown;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UPaperFlipbook* BaseFlipbookLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
    UPaperFlipbook* BaseFlipbookRight;

	// DeadFlipbook
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* DeadFlipbookUp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* DeadFlipbookDown;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* DeadFlipbookLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* DeadFlipbookRight;
	
	// FrightenFlipbook
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FrightenFlipbookUp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FrightenFlipbookDown;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FrightenFlipbookLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FrightenFlipbookRight;
	
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
	FTimerHandle FrightenedTimerHandle;
	// UFUNCTION()
	// void OnOverlap(AActor* MyActor, AActor* OtherActor);
	
};
