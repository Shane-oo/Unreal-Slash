#include "Pawns/Bird.h"

#include "Components/CapsuleComponent.h"

// #region Constructors

ABird::ABird()
{
    // Set this pawn to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    Capsule->SetCapsuleHalfHeight(20.f);
    Capsule->SetCapsuleRadius(15.f);
    SetRootComponent(Capsule);

    BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
    BirdMesh->SetupAttachment(GetRootComponent());
}

// #endregion

// #region Protected Methods

void ABird::BeginPlay()
{
    Super::BeginPlay();
}

// #endregion

// #region Public Methods

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABird::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// #endregion
