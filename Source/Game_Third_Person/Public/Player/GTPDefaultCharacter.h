// Game_Third_Person Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GTPDefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GAME_THIRD_PERSON_API AGTPDefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGTPDefaultCharacter();

protected:

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USpringArmComponent *SpringArmComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UCameraComponent *CameraComponent;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    float YRotation = -75.0f;
	float ArmLength = 1400.0f;
    float FOV = 55.0f;


	void MoveForward(float Value);
    void MoveRight(float Value);
};

