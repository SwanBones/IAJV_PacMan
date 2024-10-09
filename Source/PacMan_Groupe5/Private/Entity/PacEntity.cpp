// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/PacEntity.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APacEntity::APacEntity()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create BoxComponent and set as RootComponent for the Actor
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	// Create StaticMeshComponent and Attach to BoxComponent
	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh->SetupAttachment(BoxCollision);
	// Create FlipbookComponent and attach to BoxComponent
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->SetupAttachment(BoxCollision);
	
	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent0"));
	MovementComponent->UpdatedComponent = BoxCollision;

	
	// initialize through relative path (DON'T) need to find a way to dynamically allocate variables
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookUpAsset(TEXT("Animations"));
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookDownAsset(TEXT("Animations"));
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookLeftAsset(TEXT("Animations"));
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FlipbookRightAsset(TEXT("Animations"));

	
	/*
	if (FlipbookUpAsset.Succeeded()) FlipbookUp = FlipbookUpAsset.Object;
	if (FlipbookDownAsset.Succeeded()) FlipbookDown = FlipbookDownAsset.Object;
	if (FlipbookLeftAsset.Succeeded()) FlipbookLeft = FlipbookLeftAsset.Object;
	if (FlipbookRightAsset.Succeeded()) FlipbookRight = FlipbookRightAsset.Object;
	*/
}

// Called when the game starts or when spawned
void APacEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

