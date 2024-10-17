// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "GTPWeaponComponent.h"
#include "Animation/GTPReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/GTPBaseWeapon.h"

UGTPWeaponComponent::UGTPWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UGTPWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

SpawnWeapon();
	
}


// Called every frame
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
      ReloadFinish->OnNotifyReloadFinished.AddUObject(
          this, &UGTPWeaponComponent::OnNotifyReloadFinished);
      break;
    }
  }
}

void UGTPWeaponComponent::OnNotifyReloadFinished(
    USkeletalMeshComponent *SkeletalMesh) {
  const auto Character = Cast<ACharacter>(GetOwner());
  if (Character->GetMesh() == SkeletalMesh) {
    AnimReloading = false;
  }
}

bool UGTPWeaponComponent::CanReload() const 
{ 
    return !AnimReloading; 
}

void UGTPWeaponComponent::Reload() {
  if (!CanReload())
    return;
  Weapon->ChangeClip();
  AnimReloading = true;
  ACharacter *Character = Cast<ACharacter>(GetOwner());
  Character->PlayAnimMontage(ReloadMontage);
}

void UGTPWeaponComponent::Fire() {
  if (Weapon && !AnimReloading) {
    Weapon->Fire();
  }
}

