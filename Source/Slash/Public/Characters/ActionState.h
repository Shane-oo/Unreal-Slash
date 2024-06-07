#pragma once

UENUM(BlueprintType)
enum class EActionState: uint8
{
    EAS_UnOccupied UMETA(DisplayName = "Unoccupied"),
    EAS_Attacking UMETA(DisplayName = "Attacking"),
    EAS_EquippingWeapon UMETA(DisplayNme = "Equipping Weapon")
};