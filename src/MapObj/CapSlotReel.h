#pragma once

#include "Library/LiveActor/LiveActor.h"

#include <prim/seadEnum.h>

class CapSlotReel : public al::LiveActor {
public:

    SEAD_ENUM(ItemType, );

    CapSlotReel(const char* name, al::LiveActor* actor1, al::LiveActor* actor2);
    void init(const al::ActorInitInfo& info) override;
    void appear() override;

    void getItemType() const;
    bool isStopped() const;
    bool isDecidedItem() const;
    bool isCapHit(const al::SensorMsg* message, al::HitSensor* other, al::HitSensor* self) const;
    bool receiveMsg(const al::SensorMsg* message, al::HitSensor* other, al::HitSensor* self) override;
    void reset();
    void updatePose();

    void exeMoveStart();
    void exeMove();
    void exeHit();
    void exeStop();

private:
    al::LiveActor* mActor;
    al::LiveActor* mActor2;
    sead::Matrix34f* mPoseMtx = nullptr;
    s32 mArrayLength = 0;
    LiveActor** mActorArray = nullptr;
    s32 _130 = 0;
    f32 mAnimFrameRate = 1.0;
};