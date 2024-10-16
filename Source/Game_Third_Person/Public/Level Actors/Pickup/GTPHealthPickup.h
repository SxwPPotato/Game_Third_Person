// Game_Third_Person Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GTPHealthPickup.generated.h"

class USphereComponent;
class AGTPDefaultCharacter;

UCLASS()
class GAME_THIRD_PERSON_API AGTPHealthPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AGTPHealthPickup();

protected:
        UPROPERTY(VisibleAnywhere, Category = "Pickup")
        USphereComponent *SphereComponent;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
        float RespawnTime = 5.0f;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup",
                  meta = (ClampMin = "5.0", ClampMax = "100.0"))
        float HealthFromPickup = 100.0f;

        virtual void BeginPlay() override;
        virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
  bool GivePickup(AGTPDefaultCharacter *Character);
  void PickupWasTaken();
  void RespawnPickup();
};
