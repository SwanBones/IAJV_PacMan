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

	FVector CurrentDirection = FVector(1.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FlipbookUp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FlipbookDown;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FlipbookLeft;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* FlipbookRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int Score = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Life")
	int Lives = 3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Classe du widget GameOver
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UGameOverScreen> GameOverScreenClass;

private:
	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* MyActor, AActor* OtherActor);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUpDown(float value);

	void MoveLeftRight(float value);

	void LoseLife();

	// Compteur pour le nombre de Pac-Gommes collectées
	UPROPERTY(BlueprintReadOnly, Category = "PacMan")
	int32 PacGumCount = 0;

	// Compteur total de Pac-Gommes dans le niveau
	UPROPERTY(BlueprintReadOnly, Category = "PacMan")
	int32 TotalPacGumCount = 0;

};
