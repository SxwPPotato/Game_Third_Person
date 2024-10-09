// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "Player/GTPDefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AGTPDefaultCharacter::AGTPDefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->SetUsingAbsoluteRotation(true);
    SpringArmComponent->TargetArmLength = ArmLength;
    SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
    SpringArmComponent->bDoCollisionTest = false;
    SpringArmComponent->bEnableCameraLag = true;


    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->SetFieldOfView(FOV);
    CameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AGTPDefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGTPDefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGTPDefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAxis("MoveForward", this, &AGTPDefaultCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this,&AGTPDefaultCharacter::MoveRight);
}

void AGTPDefaultCharacter::MoveForward(float Value) {
  AddMovementInput(GetActorForwardVector(), Value);
}
void AGTPDefaultCharacter::MoveRight(float Value) {
  AddMovementInput(GetActorRightVector(), Value);
}