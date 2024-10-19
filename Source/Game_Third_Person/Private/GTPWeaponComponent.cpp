// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "GTPWeaponComponent.h"
#include "Animation/GTPReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/GTPBaseWeapon.h"

UGTPWeaponComponent::UGTPWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UGTPWeaponComponent::Fire() {
  if (Weapon && !AnimReloading) {
    Weapon->Fire();
  }
}

void UGTPWeaponComponent::StopFire() {
  if (Weapon && !AnimReloading) {
    Weapon->StopFire();
  }
}

void UGTPWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    SpawnWeapon();
    InitAnimNotify();
}

void UGTPWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGTPWeaponComponent::SpawnWeapon() {
  Weapon = GetWorld()->SpawnActor<AGTPBaseWeapon>(WeaponClass);
  if (Weapon) {
    const auto Character = Cast<ACharacter>(GetOwner());
    if (Character) {
      FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,false);
      Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_Weapon_Socket");
    }
  }
}
void UGTPWeaponComponent::InitAnimNotify() {
  if (!ReloadMontage)
    return;
  const auto NotifiesEvents = ReloadMontage->Notifies;
  for (auto NotifyEvent : NotifiesEvents) {
    auto ReloadFinish = Cast<UGTPReloadFinishedAnimNotify>(NotifyEvent.Notify);
    if (ReloadFinish) {
      ReloadFinish->OnNotifyReloadFinisheds.AddUObject(this, &UGTPWeaponComponent::OnNotifyReloadFinished);
      break;
    }
  }
}

void UGTPWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent *SkeletalMesh) {
  const auto Character = Cast<ACharacter>(GetOwner());
  UE_LOG(LogTemp, Display, TEXT("Reload finish    "));
  if (Character->GetMesh() == SkeletalMesh) {
    AnimReloading = false;
  }
}

bool UGTPWeaponComponent::CanReload() const {
  Weapon->ChangeClip();
  return !AnimReloading  ;
}

void UGTPWeaponComponent::Reload() {
  if (!CanReload())
    return;
  UE_LOG(LogTemp, Display, TEXT("Reload start                   "));
  AnimReloading = true;
  ACharacter *Character = Cast<ACharacter>(GetOwner());
  Character->PlayAnimMontage(ReloadMontage);
}




 // UE_LOG(LogTemp, Display,TEXT(""));
