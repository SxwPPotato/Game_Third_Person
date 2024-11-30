// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "Level Actors/Pickup/GTPHealthPickup.h"
#include "Components/LMAHealthComponent.h"
#include "Components/SphereComponent.h"
#include "Player/GTPDefaultCharacter.h"

AGTPHealthPickup::AGTPHealthPickup()
{

  PrimaryActorTick.bCanEverTick = true;

  SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
  SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  SphereComponent->SetCollisionResponseToAllChannels(
      ECollisionResponse::ECR_Overlap);
  SetRootComponent(SphereComponent);

}

void AGTPHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGTPHealthPickup::NotifyActorBeginOverlap(AActor *OtherActor) {
  Super::NotifyActorBeginOverlap(OtherActor);
  const auto Charcter = Cast<AGTPDefaultCharacter>(OtherActor);
  if (Charcter != nullptr) {
    if (GivePickup(Charcter)) {
      PickupWasTaken();
    }
  }
}

void AGTPHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGTPHealthPickup::GivePickup(AGTPDefaultCharacter *Character) {
  const auto HealthComponent = Character->GetHealthComponent();
  if (!HealthComponent)
    return false;

  return HealthComponent->AddHealth(HealthFromPickup);
}

void AGTPHealthPickup::PickupWasTaken() {
  SphereComponent->SetCollisionResponseToAllChannels(
      ECollisionResponse::ECR_Ignore);
  GetRootComponent()->SetVisibility(false, true);

  FTimerHandle RespawnTimerHandle;
  GetWorldTimerManager().SetTimer(
      RespawnTimerHandle, this, &AGTPHealthPickup::RespawnPickup, RespawnTime);
}

void AGTPHealthPickup::RespawnPickup() {
  SphereComponent->SetCollisionResponseToAllChannels(
      ECollisionResponse::ECR_Overlap);
  GetRootComponent()->SetVisibility(true, true);
}

