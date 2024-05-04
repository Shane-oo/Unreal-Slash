#include "Items/Item.h"

#include "Slash/DebugMacros.h"

// #region Constructors
AItem::AItem()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// #endregion

// #region Protected Methods

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
    Super::BeginPlay();
}

// #endregion


// #region Public Methods

// Called every frame
void AItem::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);

    RunningTime += DeltaTime;

    const float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);

    AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));

    const FVector Location = GetActorLocation();
    DRAW_SPHERE_SINGLE_FRAME(Location);
    DRAW_VECTOR_SINGLE_FRAME(Location, Location + GetActorForwardVector() * 100.f);
}

// #endregion
