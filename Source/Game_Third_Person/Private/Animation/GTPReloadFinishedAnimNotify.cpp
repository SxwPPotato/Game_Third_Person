// Game_Third_Person Game by Netologiya. All RightsReserved.


#include "Animation/GTPReloadFinishedAnimNotify.h"

void UGTPReloadFinishedAnimNotify::Notify(USkeletalMeshComponent *MeshComp,
                                          UAnimSequenceBase *Animation) {
  OnNotifyReloadFinished.Broadcast(MeshComp);
  Super::Notify(MeshComp, Animation);
}