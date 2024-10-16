// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pac_Gomme.generated.h"

UCLASS()
class PACMAN_GROUPE5_API APac_Gomme : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isSuper;
	
	
public:	
	// Sets default values for this actor's properties
	APac_Gomme();
	int giveScore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool getIsSuper();
};
