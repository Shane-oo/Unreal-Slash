#include "Items/Item.h"

#include "Slash/DebugMacros.h"

// #region Constructors
AItem::AItem()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
    RootComponent = ItemMesh;
}

// #endregion

// #region Protected Methods

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
    Super::BeginPlay();
}

float AItem::TransformSin() const
{
    return Amplitude * FMath::Sin(RunningTime * TimeConstant);;
}

float AItem::TransformCos() const
{
    return Amplitude * FMath::Cos(RunningTime * TimeConstant);;
}

// #endregion


// #region Public Methods

// Called every frame
void AItem::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);

    RunningTime += DeltaTime;
}

// #endregion
