#pragma once

#include <basis/seadTypes.h>

#include "Library/Event/IEventFlowEventReceiver.h"
#include "Library/LiveActor/LiveActor.h"

namespace al {
class IEventFlowQueryJudge {};
}  // namespace al

class SphinxRide : public al::LiveActor,
                   public al::IEventFlowEventReceiver,
                   public al::IEventFlowQueryJudge {
public:
    SphinxRide(const char* name);

    void init(const al::ActorInitInfo& info) override;
    void updateJointPose();
    void initAfterPlacement() override;
    void movement() override;
    void control() override;
    void requestGetOffForce();
    bool receiveEvent(const al::EventFlowEventData* event) override;
    bool
    judgeQuery(const char*);  // this should override the base judgeQuery from IEventFlowQueryJudge,
                              // but I don't know where to create the relevant header file for
                              // IEventFlowEventReceiver given that it doesn't have its own TU
    void updateCollider() override;
    void calcAnim() override;
    void attackSensor(al::HitSensor* self, al::HitSensor* other) override;
    bool receiveMsg(const al::SensorMsg* message, al::HitSensor* self,
                    al::HitSensor* other) override;
    void disappear();
    bool isCanRidePlacement();
    void startClipped() override;

    void exeWait();
    void exeStandby();
    void setNerveFall();
    bool trySlipOnMoveLimit();
    void exeReaction();
    void exeDemoStandbyStart();
    void exeDemoStandbyTurnZero();
    void exeDemoTurnEnd();
    void exeGetOnStart();
    void exeGetOnStartOn();
    void exeGetOn();

    bool isValidateCameraAngleV(f32);

    void exeRun();
    bool tryGetOffAndCancelBind();
    void updateRun(f32);
    void exeClash();
    void updateGravityAndDump(f32, f32);
    void exeStop();
    void sendMsgCollidedCactus();
    void exeFall();
    void controlAndRotateYAndMove(f32, f32, bool);
    void exeLand();
    void exeGetOff();
    void exeJump();
    void exeRevival();
    void exeEventWait();

    bool isRidePlayer() const;
    bool isPlayerInputSwingSphinxStop() const;

    void sendMsgCollidedTouch();
    bool calcCheckCollidedWallCommon(sead::Vector3f*, sead::Vector3f*, al::HitSensor**,
                                     al::HitSensor**);

    void startStandby(const sead::Vector3f&, const sead::Vector3f&);
    bool isNerveStandby() const;
    void setupEventFade();
    void startEventWait();
    void endEventWait(f32);

private:
    char filler[0x330];
};

f32 calcRunSpeedRate(const al::LiveActor* actor);

static_assert(sizeof(SphinxRide) == 0x440);
