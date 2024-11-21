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
#include "GTPWeaponComponent.h"
#include "GameFramework/Controller.h"


AGTPDefaultCharacter::AGTPDefaultCharacter()
{
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

    WeaponComponent = CreateDefaultSubobject<UGTPWeaponComponent>("Weapon");
}

void AGTPDefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
    if (CursorMaterial) {
        CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
    }

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUniqueDynamic(this,&AGTPDefaultCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AGTPDefaultCharacter::OnHealthChanged);
}

void AGTPDefaultCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
    if (!(HealthComponent->IsDead())) {
        RotationPlayerOnCursor();
    }
    if (SwitchSprint == true && Endurance >0) {
      Endurance -= 1;
      GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("endurance = %i"), Endurance));
    }
    if (SwitchSprint == false && Endurance < 100) {
      Endurance += 1;
      GEngine->AddOnScreenDebugMessage( -1, 2.0f, FColor::Blue,FString::Printf(TEXT("endurance = %i"), Endurance));
    }
    if (Endurance == 0){
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
  PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UGTPWeaponComponent::Fire);
  PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent,&UGTPWeaponComponent::StopFire);
  PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent,&UGTPWeaponComponent::Reload);
}

void AGTPDefaultCharacter::MoveForward(float Value) {
  AddMovementInput(GetActorForwardVector(), Value);
}
void AGTPDefaultCharacter::MoveRight(float Value) {
  AddMovementInput(GetActorRightVector(), Value);
}

void AGTPDefaultCharacter::SprintStart() {
  SwitchSprint = true;
  if (Endurance > 0) {
    comp->MaxWalkSpeed = SprintSpeed;
  }
}

void AGTPDefaultCharacter::SprintStop() {
  SwitchSprint = false;
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