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

    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// #endregion

// #region Protected Methods

void ABird::BeginPlay()
{
    Super::BeginPlay();
}

void ABird::MoveForward(float Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);
}

// #endregion

// #region Public Methods

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
}

void ABird::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// #endregion
