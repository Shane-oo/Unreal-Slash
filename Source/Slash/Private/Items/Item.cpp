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

    const FVector Location = GetActorLocation();
    const FVector Forward = GetActorForwardVector();

    DRAW_SPHERE(Location);
    DRAW_VECTOR(Location, Location + Forward * 100.f);
}

// #endregion


// #region Public Methods

// Called every frame
void AItem::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}
