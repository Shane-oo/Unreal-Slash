#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Bird.generated.h"

class UCameraComponent;
// forward declaration
class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
struct FInputActionValue;

UCLASS()
class SLASH_API ABird : public APawn
{
    GENERATED_BODY()

public:
    ABird();
    virtual void Tick(float DeltaTime) override;
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
    UInputMappingContext* BirdMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
    UInputAction* MoveAction;

    void Move(const FInputActionValue& Value);

private:
    UPROPERTY(VisibleAnywhere)
    UCapsuleComponent* Capsule;

    UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* BirdMesh;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ViewCamera;
};
