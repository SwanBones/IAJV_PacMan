// Fill out your copyright notice in the Description page of Project Settings.

#include "Screens/GameOverScreen.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOverScreen::NativeConstruct()
{
	Super::NativeConstruct();

	// Assurez-vous que les widgets sont valides avant d'y accéder
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverScreen::OnRestartButtonClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UGameOverScreen::OnQuitButtonClicked);
	}
}

void UGameOverScreen::UpdateScore(const int FinalScore)
{
	if (Score)
	{
		Score->SetText(FText::FromString(FString::Printf(TEXT("Your Score : %d"), FinalScore)));
	}
}

void UGameOverScreen::OnRestartButtonClicked()
{
	// Recharge le niveau actuel pour redémarrer le jeu
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UGameOverScreen::OnQuitButtonClicked()
{
	// Quitter le jeu
	UGameplayStatics::SetGamePaused(this, true);
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
