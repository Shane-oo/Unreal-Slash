#include "Items/Item.h"

#include "Characters/SlashCharacter.h"
#include "Components/SphereComponent.h"

// #region Private Methods

void AItem::Hover(const float DeltaTime)
{
    constexpr int MovementRate = 75;
    AddActorWorldRotation(FRotator(0, MovementRate * DeltaTime, 0));

    AddActorWorldOffset(FVector(0.f, TransformCos(), TransformSin()));
}

// #endregion

// #region Constructors
AItem::AItem()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
    SetRootComponent(ItemMesh);

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->SetupAttachment(GetRootComponent());
}

// #endregion

// #region Protected Methods

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
    Super::BeginPlay();

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
    SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

float AItem::TransformSin() const
{
    return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformCos() const
{
    return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
    if (ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor))
    {
        SlashCharacter->SetOverlappingItem(this);
    }
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor))
    {
        SlashCharacter->SetOverlappingItem(nullptr);
    }
}

// #endregion


// #region Public Methods

// Called every frame
void AItem::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);

    RunningTime += DeltaTime;

    if(ItemState == EItemState::EIS_Hovering)
    {
        Hover(DeltaTime);
    }
}

// #endregion
