// Game_Third_Person Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GTPBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UGTPWeaponComponent;

DECLARE_MULTICAST_DELEGATE(FOnNotifyChangeClipSignature);

USTRUCT(BlueprintType)
struct FAmmoWeapon {
  GENERATED_USTRUCT_BODY()
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  int32 Bullets;
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  int32 Clips;
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  bool Infinite;
};

UCLASS()
class GAME_THIRD_PERSON_API AGTPBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AGTPBaseWeapon();
    void Fire();
    void ChangeClip();
    void StopFire();
    FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent *WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoWeapon AmmoWeapon{30, 0, true};

    void Shoot();
    

	virtual void BeginPlay() override;

    void DecrementBullets();
    bool IsCurrentClipEmpty() const;

    UGTPWeaponComponent *weap;
  

public:	

	virtual void Tick(float DeltaTime) override;
    bool shooting = false;
    FTimerHandle RecoveryTimer;
    FOnNotifyChangeClipSignature OnNotifyEmptyClip;
    

    bool FullAmmo();

    //void CallbackFunc();

  private:
  FAmmoWeapon CurrentAmmoWeapon;
  

};
