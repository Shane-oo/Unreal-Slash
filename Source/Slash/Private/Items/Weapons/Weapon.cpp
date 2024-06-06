#include "Items/Weapons/Weapon.h"

#include "Characters/SlashCharacter.h"

// #region Protected Methods
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

// #endregion 

// #region Public Methods

void AWeapon::Equip(USceneComponent* InParentComponent, const FName SocketName) const
{
    const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,
                                                   EAttachmentRule::SnapToTarget,
                                                   EAttachmentRule::SnapToTarget,
                                                   false);
    ItemMesh->AttachToComponent(InParentComponent, TransformRules, SocketName);
}

// #endregion
