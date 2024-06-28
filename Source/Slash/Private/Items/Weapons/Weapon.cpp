#include "Items/Weapons/Weapon.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Interfaces/Hit.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// #region Private Methods


// #endregion


// #region Constructors

AWeapon::AWeapon()
{
    WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
    WeaponBox->SetupAttachment(GetRootComponent());

    SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponBox->SetCollisionResponseToAllChannels(ECR_Overlap);
    // Ignore Pawn Channel
    WeaponBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

    BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
    BoxTraceStart->SetupAttachment(GetRootComponent());

    BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
    BoxTraceEnd->SetupAttachment(GetRootComponent());
}

// #endregion

// #region Protected Methods

void AWeapon::BeginPlay()
{
    Super::BeginPlay();

    WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
    Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const FVector Start = BoxTraceStart->GetComponentLocation();
    const FVector End = BoxTraceEnd->GetComponentLocation();

    // Dont hit weapon itself
    ActorsToIgnore.AddUnique(this);

    FHitResult BoxHit;

    UKismetSystemLibrary::BoxTraceSingle(
        this,
        Start,
        End,
        FVector(5.f, 5.f, 5.f),
        BoxTraceStart->GetComponentRotation(),
        TraceTypeQuery1, // Does nothing
        false,
        ActorsToIgnore,
        EDrawDebugTrace::ForDuration,
        BoxHit,
        true
    );

    if (AActor* BoxHitActor = BoxHit.GetActor())
    {
        if (IHit* HitActor = Cast<IHit>(BoxHitActor))
        {
            HitActor->GetHit(BoxHit.ImpactPoint);

            ActorsToIgnore.AddUnique(BoxHitActor);
        }
    }
}

// #endregion 

// #region Public Methods

void AWeapon::AttachMeshToSocket(USceneComponent* InParentComponent, const FName SocketName) const
{
    const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,
                                                   EAttachmentRule::SnapToTarget,
                                                   EAttachmentRule::SnapToTarget,
                                                   true);
    ItemMesh->AttachToComponent(InParentComponent, TransformRules, SocketName);
}


void AWeapon::Equip(USceneComponent* InParentComponent, const FName SocketName)
{
    AttachMeshToSocket(InParentComponent, SocketName);
    ItemState = EItemState::EIS_Equipped;

    if (EquipSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, EquipSound, GetActorLocation());
    }

    // Disable Collisions with Weapon after Equipping
    if (SphereComponent)
    {
        SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void AWeapon::SetWeaponCollisionEnabled(const ECollisionEnabled::Type CollisionEnabled)
{
    if (WeaponBox)
    {
        WeaponBox->SetCollisionEnabled(CollisionEnabled);
        if (CollisionEnabled == ECollisionEnabled::NoCollision)
        {
            ActorsToIgnore.Empty();
        }
    }
}


// #endregion
