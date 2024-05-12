#include "Pawns/Bird.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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

    if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(BirdMappingContext, 0);
        }
    }
}

void ABird::Move(const FInputActionValue& Value)
{
    const bool CurrentValue = Value.Get<bool>();
    if (CurrentValue)
    {
        UE_LOG(LogTemp, Warning, TEXT("IA_Move triggered"));
    }
}

// #endregion

// #region Public Methods

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up actions
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
    }
}

void ABird::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// #endregion
