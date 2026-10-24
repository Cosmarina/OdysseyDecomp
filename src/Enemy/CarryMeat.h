#pragma once

#include "Library/LiveActor/LiveActor.h"

#include "Demo/IUseDemoSkip.h"



class BirdCarryMeat;
class CapTargetInfo;
class IUsePlayerHack;
class PlayerHackStartShaderCtrl;
class WaveSurfMapParts;

namespace al {
class CameraTicket;
class JointSpringControllerHolder;
}   // namespace al

class CarryMeat : public al::LiveActor, public IUseDemoSkip {
public:
    CarryMeat(const char* name);

    void init(const al::ActorInitInfo& info) override;
    void validateHack();
    bool receiveMsg(const al::SensorMsg* message, al::HitSensor* other,
                    al::HitSensor* self) override;
    void endHack();
    void reset();
    void control() override;
    bool isFirstDemo() const override;
    bool isEnableSkipDemo() const override;
    void skipDemo() override;
    void endDemoAndBind(const sead::Matrix34f*);

    bool isWaiting() const;
    bool isBindable() const;
    bool isCarryReaction() const;

    void startDemo();
    void drop();
    void addDemoActor();

    void exeWaitSalt();
    void exeWait();
    void exeHackStart();
    void exeHackSalt();
    void exeHackSaltJump();
    void exeHack();
    void exeReactionJump();
    void exeReactionHipDrop();
    void exeHackMoveWait();
    void exeHackMove();
    void exeHackJump();
    void exeHackJumpEnd();
    void exeHackBindable();
    void exeDemoCarryMeat();
    void exeHackBind();
    void exeHackBindReaction();
    void exeHackFall();
    void exeSurf();

    void setParent(BirdCarryMeat* parent) { mParent = parent; }

private:
    BirdCarryMeat* mParent = nullptr;
    IUsePlayerHack* mPlayerHack;
    CapTargetInfo* mCapTargetInfo;
    WaveSurfMapParts* mWaveSurfMapParts;
    PlayerHackStartShaderCtrl* mPlayerHackStartShaderCtrl;
    PlayerHackStartShaderCtrl* mPlayerHackStartShaderCtrl2;
    al::CameraTicket* mCameraTicket;
    al::JointSpringControllerHolder* mJointSpringControllerHolder;
    sead::Matrix34f* _150;
    sead::Quatf _158 = sead::Quatf::unit;
    sead::Vector3f _168 = sead::Vector3f::zero;
    char _174[0xB];
    u8 _17F;
    u8 _180;
    u8 _181;
    u8 _182;
    u8 _183;
    sead::Quatf _184 = sead::Quatf::unit;
    sead::Quatf _194 = sead::Quatf::unit;
};

static_assert(sizeof(CarryMeat) == 0x1a8);
