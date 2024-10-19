// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Pac_Gomme.h"
#include "Components/BoxComponent.h"

int APac_Gomme::giveScore()
{
    int tempScore = isSuper ? 200: 100;

    Destroy();
    return tempScore;
    
}

// Sets default values
APac_Gomme::APac_Gomme()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // Create BoxComponent and set as RootComponent for the Actor
    BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
    RootComponent = BoxCollision;

    // Create StaticMeshComponent and Attach to BoxComponent
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void APac_Gomme::BeginPlay()
{
	Super::BeginPlay();
    if (isSuper) {
        BoxCollision->SetRelativeScale3D(FVector(3.f, 3.f, 3.f)) ;
    }
	
}

// Called every frame
void APac_Gomme::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APac_Gomme::getIsSuper()
{
    return isSuper;
}

