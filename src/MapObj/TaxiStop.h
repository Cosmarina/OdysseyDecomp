#pragma once

#include "Library/Event/IEventFlowEventReceiver.h"
#include "Library/Event/IEventFlowQueryJudge.h"
#include "Library/LiveActor/LiveActor.h"

class SphinxRide;

class TaxiStop : public al::LiveActor,
                 public al::IEventFlowEventReceiver,
                 public al::IEventFlowQueryJudge {
public:
    TaxiStop(const char* name, SphinxRide* sphinxRide);

    void init(const al::ActorInitInfo& info) override;
    bool receiveMsg(const al::SensorMsg* message, al::HitSensor* self,
                    al::HitSensor* other) override;
    bool receiveEvent(const al::EventFlowEventData* event) override;
    bool judgeQuery(const char*) override;

    void exeWait();
    void exeNoPay();
    void exeWarpMenu();
    void exePlayerBind();
    void exeSphinxNear();
    void exeReaction();
    void exeWaitMinigame();
    void exeReactionMinigame();

    void setNerveWaitOrNoPay();
    void setNervePlayerBind();

    sead::Vector3f getTrans() { return mTrans; }
    sead::Vector3f getRot() { return mRot; }

private:
    char filler[0x10];
    sead::Vector3f mTrans;
    sead::Vector3f mRot;
    char moreFiller[0x28];
};

static_assert(sizeof(TaxiStop) == 0x168);
