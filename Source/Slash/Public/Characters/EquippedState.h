#pragma once

UENUM(BlueprintType)
enum class EEquippedState: uint8
{
    EES_UnEquipped UMETA(DisplayName = "UnEquipped"),
    EES_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Handed Weapon"),
    EES_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Handed Weapon")
};