#include "Items/Weapons/Weapon.h"

#include "Characters/SlashCharacter.h"

// #region Protected Methods
void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
    Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (const ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor))
    {
        const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,
                                                       EAttachmentRule::SnapToTarget,
                                                       EAttachmentRule::SnapToTarget,
                                                       false);
        ItemMesh->AttachToComponent(SlashCharacter->GetMesh(), TransformRules, SlashCharacter->GetRightHandSocket());
    }
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}


// #endregion 
