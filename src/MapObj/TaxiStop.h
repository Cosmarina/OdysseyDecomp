#pragma once

#include "Library/Event/IEventFlowEventReceiver.h"
#include "Library/LiveActor/LiveActor.h"

namespace al {
class IEventFlowQueryJudge {};
}  // namespace al

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
    bool
    judgeQuery(const char*);  // this should override the base judgeQuery from IEventFlowQueryJudge,
                              // but I don't know where to create the relevant header file for
                              // IEventFlowEventReceiver given that it doesn't have its own TU

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

private:
    char filler[0x58];
};

static_assert(sizeof(TaxiStop) == 0x168);
