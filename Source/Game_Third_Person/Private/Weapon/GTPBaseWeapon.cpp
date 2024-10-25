// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "Weapon/GTPBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GTPWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

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
{ Super::Tick(DeltaTime); }

void AGTPBaseWeapon::Fire() 
{ 
    shooting = true;
  GetWorldTimerManager().SetTimer(RecoveryTimer, this, &ThisClass::Shoot,0.2f,true);
}
void AGTPBaseWeapon::StopFire() 
{ 
    GetWorldTimerManager().ClearTimer(RecoveryTimer);
    shooting = false;
}

void AGTPBaseWeapon::SpawnTrace(const FVector &TraceStart,const FVector &TraceEnd) 
{
  const auto TraceFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceEffect, TraceStart);
  if (TraceFX) {
    TraceFX->SetNiagaraVariableVec3(TraceName, TraceEnd);
  }

}

void AGTPBaseWeapon::Shoot() {
    const FTransform SocketTransform =
        WeaponComponent->GetSocketTransform("Muzzle");
    const FVector TraceStart = SocketTransform.GetLocation();
    const FVector ShootDirection =
        SocketTransform.GetRotation().GetForwardVector();
    const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd,
                                         ECollisionChannel::ECC_Visibility);
    FVector TracerEnd = TraceEnd;
    if (HitResult.bBlockingHit) {
      TracerEnd = HitResult.ImpactPoint;
    }
    SpawnTrace(TraceStart, TracerEnd);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootWave, TraceStart);
    DecrementBullets();

}


void AGTPBaseWeapon::ChangeClip() {
    if (CurrentAmmoWeapon.Bullets != AmmoWeapon.Bullets) {
      CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
    }
  }

void AGTPBaseWeapon::DecrementBullets() {
  CurrentAmmoWeapon.Bullets--;
  UE_LOG(LogWeapon, Display, TEXT("Bullets = %s"),*FString::FromInt(CurrentAmmoWeapon.Bullets));
  if (IsCurrentClipEmpty()) {
    UE_LOG(LogTemp, Display, TEXT("Broadcast"));
  OnNotifyEmptyClip.Broadcast();

    //ChangeClip();
  }
}

bool AGTPBaseWeapon::IsCurrentClipEmpty() const {
  if (CurrentAmmoWeapon.Bullets == 0)
  UE_LOG(LogTemp, Display, TEXT("Clip Empty"));
  return CurrentAmmoWeapon.Bullets == 0;
}

bool AGTPBaseWeapon::FullAmmo() { 
    if(CurrentAmmoWeapon.Bullets == 30)
    {
        return false;
    } 
    else 
    {
        return true;
    }
}

