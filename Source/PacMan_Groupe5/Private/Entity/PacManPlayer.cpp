// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/PacManPlayer.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include <Entity/Pac_Gomme.h>

#include "EngineUtils.h"
#include "Entity/Ghost.h"

// Sets default values
APacManPlayer::APacManPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APacManPlayer::BeginPlay()
{
	Super::BeginPlay();
	// Bind function OnActorBeginOverlap with your class function OnOverlap
	this->OnActorBeginOverlap.AddDynamic(this, &APacManPlayer::OnOverlap);

	// Bind function OnActorBeginOverlap with your class function EndOverlap
	this->OnActorEndOverlap.AddDynamic(this, &APacManPlayer::OnEndOverlap);
	Score = 0;
}

void APacManPlayer::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto gomme = Cast<APac_Gomme>(OtherActor)) {
		Score += gomme->giveScore();
		if (gomme->getIsSuper()) {
			//ajouter killmode
			// Parcours tous les fantômes dans la scène
			for (TActorIterator<AGhost> GhostItr(GetWorld()); GhostItr; ++GhostItr)
			{
				AGhost* Ghost = *GhostItr;
				if (Ghost)
				{
					// Appelle la méthode qui gère l'état effrayé (si nécessaire)
					Ghost->SetFrightenMode();
				}
			}
		}
	}
}

void APacManPlayer::OnEndOverlap(AActor* MyActor, AActor* OtherActor)
{
}

// Called every frame
void APacManPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(CurrentDirection, 1.0);
}

// Called to bind functionality to input
void APacManPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUpDown", this, &APacManPlayer::MoveUpDown);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &APacManPlayer::MoveLeftRight);
}

void APacManPlayer::MoveUpDown(float value)
{
	if (value < 0.0f)  // Vers la haut
	{
		// Assigner un Flipbook spécifique pour l'animation du mouvement vers le haut
		FlipbookComponent->SetFlipbook(FlipbookUp);
		CurrentDirection = FVector(0.0f, -1.0f, 0.0f);
	}
	else if (value > 0.0f)  // Vers la bas
	{
		// Assigner un Flipbook spécifique pour l'animation du mouvement vers la bas
		FlipbookComponent->SetFlipbook(FlipbookDown);
		CurrentDirection = FVector(0.0f, 1.0f, 0.0f);
	}
	
	// FVector Direction = FVector(0.0f, 1.0f, 0.0f);
	// AddMovementInput(Direction, value);
}

void APacManPlayer::MoveLeftRight(float value)
{
	if (value > 0.0f)  // Vers la droite
	{
		// Assigner un Flipbook spécifique pour l'animation du mouvement vers la droite
		FlipbookComponent->SetFlipbook(FlipbookRight);
		CurrentDirection = FVector(1.0f, 0.0f, 0.0f);
	}
	else if (value < 0.0f)  // Vers la gauche
	{
		// Assigner un Flipbook spécifique pour l'animation du mouvement vers la gauche
		FlipbookComponent->SetFlipbook(FlipbookLeft);
		CurrentDirection = FVector(-1.0f, 0.0f, 0.0f);
	}
	
	// FVector Direction = FVector(1.0f, 0.0f, 0.0f);
	// AddMovementInput(Direction, value);
}

