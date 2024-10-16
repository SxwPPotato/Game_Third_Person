// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "Player/GTPDefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/LMAHealthComponent.h"
#include "String"
#include "GameFramework/CharacterMovementComponent.h"

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

    HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void AGTPDefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
    if (CursorMaterial) {
        CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
    }

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &AGTPDefaultCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AGTPDefaultCharacter::OnHealthChanged);
	
}

// Called every frame
void AGTPDefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (!(HealthComponent->IsDead())) {
        RotationPlayerOnCursor();
    }
    if (switch_sprint == true && endurance >0) {
      endurance -= 1;
      GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("endurance = %i"), endurance));
    }
    if (switch_sprint == false && endurance < 100) {
      endurance += 1;
      GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Blue,FString::Printf(TEXT("endurance = %i"), endurance));
    }
    if (endurance == 0){
      comp->MaxWalkSpeed = WalkSpeed;
    }
   
}

void AGTPDefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAxis("MoveForward",this,&AGTPDefaultCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this,&AGTPDefaultCharacter::MoveRight);
  PlayerInputComponent->BindAction("Shift", IE_Pressed, this, &AGTPDefaultCharacter::SprintStart);
  PlayerInputComponent->BindAction("Shift", IE_Released, this,&AGTPDefaultCharacter::SprintStop);

}

void AGTPDefaultCharacter::MoveForward(float Value) {
  AddMovementInput(GetActorForwardVector(), Value);
}
void AGTPDefaultCharacter::MoveRight(float Value) {
  AddMovementInput(GetActorRightVector(), Value);
 
}

void AGTPDefaultCharacter::SprintStart() {
  //UE_LOG(LogTemp, Display,TEXT("endurance: %i"), endurance);
  switch_sprint = true;
  if (endurance > 0) {
    comp->MaxWalkSpeed = SprintSpeed;
  }
}

void AGTPDefaultCharacter::SprintStop() {
  //UE_LOG(LogTemp, Display, TEXT("endurance: %i"), endurance);
  switch_sprint = false;
  comp->MaxWalkSpeed = WalkSpeed;
}

void AGTPDefaultCharacter::OnDeath() {

  CurrentCursor->DestroyRenderState_Concurrent();
  PlayAnimMontage(DeathMontage);
  GetCharacterMovement()->DisableMovement();
  SetLifeSpan(5.0f);
  if (Controller) {
    Controller->ChangeState(NAME_Spectating);
  }

}

void AGTPDefaultCharacter::RotationPlayerOnCursor() {
  APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  if (PC) {
    FHitResult ResultHit;
    PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
    float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation( GetActorLocation(), ResultHit.Location).Yaw;
    SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
    if (CurrentCursor) {
      CurrentCursor->SetWorldLocation(ResultHit.Location);
    }
  }
}

void AGTPDefaultCharacter::OnHealthChanged(float NewHealth) {
  GEngine->AddOnScreenDebugMessage(
      -1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}