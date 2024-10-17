// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "Weapon/GTPBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

AGTPBaseWeapon::AGTPBaseWeapon()
{
  PrimaryActorTick.bCanEverTick = true;
  WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
  SetRootComponent(WeaponComponent);

}

void AGTPBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

    CurrentAmmoWeapon = AmmoWeapon;
	
}

void AGTPBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGTPBaseWeapon::Fire() 
{ 
	Shoot(); 
}

void AGTPBaseWeapon::Shoot() {
  const FTransform SocketTransform =
      WeaponComponent->GetSocketTransform("Muzzle");
  const FVector TraceStart = SocketTransform.GetLocation();
  const FVector ShootDirection =
      SocketTransform.GetRotation().GetForwardVector();
  const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
  DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f, 0,
                2.0f);

  FHitResult HitResult;
  GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd,
                                       ECollisionChannel::ECC_Visibility);

  if (HitResult.bBlockingHit) {
    DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red,
                    false, 1.0f);
  }

  DecrementBullets();

}

void AGTPBaseWeapon::ChangeClip() {
  CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
}

void AGTPBaseWeapon::DecrementBullets() {
  CurrentAmmoWeapon.Bullets--;
  UE_LOG(LogWeapon, Display, TEXT("Bullets = %s"),*FString::FromInt(CurrentAmmoWeapon.Bullets));
  if (IsCurrentClipEmpty()) {
    ChangeClip();
  }
}

bool AGTPBaseWeapon::IsCurrentClipEmpty() const {
  return CurrentAmmoWeapon.Bullets == 0;
}