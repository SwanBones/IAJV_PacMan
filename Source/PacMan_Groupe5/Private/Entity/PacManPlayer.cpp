// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/PacManPlayer.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include <Entity/Pac_Gomme.h>

#include "EngineUtils.h"
#include "Entity/Ghost.h"

#include "Kismet/GameplayStatics.h"
#include "Screens/GameOverScreen.h"

// Sets default values
APacManPlayer::APacManPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsStarted = false;

	PacGumUsingFirstSound = true;
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

	// Compte le nombre de Pac-Gommes dans la scène
	TArray<AActor*> PacGumActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APac_Gomme::StaticClass(), PacGumActors);

	TotalPacGumCount = PacGumActors.Num(); // Stocke le total dans la variable
	// Affiche le nombre total de Pac-Gommes sur l'écran de débogage
	FString Message = FString::Printf(TEXT("Total de Pac-Gommes dans la scène : %d"), TotalPacGumCount);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message);
}

void APacManPlayer::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto gomme = Cast<APac_Gomme>(OtherActor)) {
		Score += gomme->giveScore();
		PacGumCount++;
		// FString Message = FString::Printf(TEXT("Nombre de PacGum manger : %d"), PacGumCount);
		// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message);

		if (PacGumUsingFirstSound && PacGumSound1)
		{
			UGameplayStatics::PlaySound2D(this, PacGumSound1);
		}
		else if (PacGumSound2)
		{
			UGameplayStatics::PlaySound2D(this, PacGumSound2);
		}

		// Alterner le son pour la prochaine fois
		PacGumUsingFirstSound = !PacGumUsingFirstSound;
		
		if (gomme->getIsSuper()) {
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
		else if (PacGumCount >= TotalPacGumCount)
		{
			if (WinScreenClass) // Vérifie que le widget est bien assigné
			{
				APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
				if (PlayerController)
				{
					UGameOverScreen* WinScreen = CreateWidget<UGameOverScreen>(PlayerController, WinScreenClass);
					if (WinScreen)
					{
						WinScreen->UpdateScore(Score);
						WinScreen->AddToViewport();  // Ajoute le widget à l'interface
						UGameplayStatics::SetGamePaused(this, true);
						PlayerController->bShowMouseCursor = true;  // Affiche le curseur de la souris
					}
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
	if(IsStarted)
	{
		AddMovementInput(CurrentDirection, 1.0);
	}
	
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
	// Vérifiez si le jeu a commencé
	if (!IsStarted && value != 0.0f) {
		IsStarted = true; // Marquez le jeu comme commencé
	}

	// Ne mettez à jour la direction et les animations que si le jeu a commencé
	if (IsStarted) {
		if (value < 0.0f)  // Vers le haut
		{
			FlipbookComponent->SetFlipbook(FlipbookUp);
			CurrentDirection = FVector(0.0f, -1.0f, 0.0f);
		}
		else if (value > 0.0f)  // Vers le bas
		{
			FlipbookComponent->SetFlipbook(FlipbookDown);
			CurrentDirection = FVector(0.0f, 1.0f, 0.0f);
		}
	}
}

void APacManPlayer::MoveLeftRight(float value)
{
	// Vérifiez si le jeu a commencé
	if (!IsStarted && value != 0.0f) {
		IsStarted = true; // Marquez le jeu comme commencé
	}

	// Ne mettez à jour la direction et les animations que si le jeu a commencé
	if (IsStarted) {
		if (value > 0.0f)  // Vers la droite
		{
			FlipbookComponent->SetFlipbook(FlipbookRight);
			CurrentDirection = FVector(1.0f, 0.0f, 0.0f);
		}
		else if (value < 0.0f)  // Vers la gauche
		{
			FlipbookComponent->SetFlipbook(FlipbookLeft);
			CurrentDirection = FVector(-1.0f, 0.0f, 0.0f);
		}
	}
}

/*void APacManPlayer::MoveUpDown(float value)
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
}*/

void APacManPlayer::LoseLife()
{
	Lives--;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("LoseLife"));
	if (Lives <= 0)
	{
		if (GameOverScreenClass) // Vérifie que le widget est bien assigné
		{
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (PlayerController)
			{
				UGameOverScreen* GameOverScreen = CreateWidget<UGameOverScreen>(PlayerController, GameOverScreenClass);
				if (GameOverScreen)
				{
					GameOverScreen->UpdateScore(Score);
					GameOverScreen->AddToViewport();  // Ajoute le widget à l'interface
					UGameplayStatics::SetGamePaused(this, true);
					PlayerController->bShowMouseCursor = true;  // Affiche le curseur de la souris
				}
			}
		}
	}
	
}

