#include "Enemy/CarryMeat.h"

#include "Library/Camera/CameraUtil.h"
#include "Library/Effect/EffectSystemInfo.h"
#include "Library/Joint/JointControllerKeeper.h"
#include "Library/Joint/JointSpringControllerHolder.h"
#include "Library/LiveActor/ActorActionFunction.h"
#include "Library/LiveActor/ActorAnimFunction.h"
#include "Library/LiveActor/ActorClippingFunction.h"
#include "Library/LiveActor/ActorCollisionFunction.h"
#include "Library/LiveActor/ActorFlagFunction.h"
#include "Library/LiveActor/ActorInitUtil.h"
#include "Library/LiveActor/ActorModelFunction.h"
#include "Library/LiveActor/ActorMovementFunction.h"
#include "Library/LiveActor/ActorPoseUtil.h"
#include "Library/LiveActor/ActorSensorUtil.h"
#include "Library/LiveActor/LiveActorFunction.h"
#include "Library/Nerve/NerveSetupUtil.h"
#include "Library/Nerve/NerveUtil.h"
#include "Library/Rail/RailUtil.h"
#include "Library/Stage/StageSwitchUtil.h"
#include "Library/Thread/FunctorV0M.h"

#include "Enemy/BirdCarryMeat.h"
#include "MapObj/WaveSurfMapParts.h"
#include "Player/PlayerHackStartShaderCtrl.h"
#include "Util/DemoUtil.h"
#include "Util/InputInterruptTutorialUtil.h"
#include "Util/PlayerHackInputFunction.h"
#include "Util/PlayerHackFunction.h"
#include "Util/SpecialBuildUtil.h"

namespace {
NERVE_IMPL(CarryMeat, WaitSalt);
NERVE_IMPL(CarryMeat, Surf);
NERVE_IMPL(CarryMeat, Wait);
NERVE_IMPL(CarryMeat, HackBindable);
NERVE_IMPL(CarryMeat, HackBind);
NERVE_IMPL(CarryMeat, HackBindReaction);
NERVE_IMPL(CarryMeat, DemoCarryMeat);
NERVE_IMPL(CarryMeat, HackFall);
NERVE_IMPL(CarryMeat, HackJump);
NERVE_IMPL(CarryMeat, HackSaltJump);
NERVE_IMPL(CarryMeat, HackSalt);
NERVE_IMPL(CarryMeat, HackStart);
NERVE_IMPL(CarryMeat, ReactionHipDrop);
NERVE_IMPL(CarryMeat, ReactionJump);
NERVE_IMPL(CarryMeat, HackMoveWait);
NERVE_IMPL(CarryMeat, HackMove);
NERVE_IMPL(CarryMeat, HackJumpEnd);

NERVES_MAKE_NOSTRUCT(CarryMeat, WaitSalt, Surf, Wait, HackBindable, HackBind, HackBindReaction, DemoCarryMeat, HackFall, HackJump, HackSaltJump, HackSalt, HackStart, ReactionHipDrop, ReactionJump, HackMoveWait, HackMove, HackJumpEnd);
}   // namespace

CarryMeat::CarryMeat(const char* name) : al::LiveActor(name) {}

PlayerHackStartShaderParam cShaderParam = {true, -1.0, 10, 20};

void CarryMeat::init(const al::ActorInitInfo& info) {
    using CarryMeatFunctor = al::FunctorV0M<CarryMeat*, void (CarryMeat::*)()>;

    al::initActor(this, info);
    al::initNerve(this, &WaitSalt, 0);

    mCapTargetInfo = rs::createCapTargetInfo(this, nullptr);

    if (al::isExistRail(this)) {
        al::setRailPosToStart(this);
        al::syncRailTrans(this);
    }

    mWaveSurfMapParts = new WaveSurfMapParts("肉（波乗り）");
    makeActorDead();
    mCameraTicket = al::initDemoAnimCamera(this, info, "Anim");
    al::startMclAnimAndSetFrameAndStop(al::getSubActor(this, "帽子の的"), "Color", 3.0f);
    _158 = al::getQuat(this);
    _168 = al::getTrans(this);

    mPlayerHackStartShaderCtrl = new PlayerHackStartShaderCtrl(al::getSubActor(this, "肉の塩釜"), &cShaderParam);
    mPlayerHackStartShaderCtrl2 = new PlayerHackStartShaderCtrl(this, &cShaderParam);

    if (rs::isModeDiverRom()) {
        al::hideModel(al::getSubActor(this, "帽子の的"));
    }

    al::startAction(al::getSubActor(this, "肉の塩釜"), "Wait");
    al::startVisAnimAndSetFrameAndStop(al::getSubActor(this, "肉の塩釜"), "CrackSmall", 0.0f);
    al::initJointControllerKeeper(this, 2);
    mJointSpringControllerHolder = new al::JointSpringControllerHolder();
    mJointSpringControllerHolder->init(this, "InitJointSpringCtrl");
    mJointSpringControllerHolder->offControlAll();

    al::hideModel(al::getSubActor(this, "帽子の的"));
    al::invalidateHitSensors(al::getSubActor(this, "帽子の的"));

    al::listenStageSwitchOn(this, "SwitchCaptureEnable", CarryMeatFunctor(this, &CarryMeat::validateHack));
    makeActorAlive();
}

// Matching
void CarryMeat::validateHack() {
    al::showModelIfHide(al::getSubActor(this, "帽子の的"));
    al::validateHitSensors(al::getSubActor(this, "帽子の的"));
    _180 = 0;
}


// Matching
void CarryMeat::endHack() {
    rs::endHack(&mPlayerHack);
    mJointSpringControllerHolder->offControlAll();
    al::startVisAnim(this, "HackOff");
    al::validateClipping(this);
}

// Matching
void CarryMeat::control() {
    al::setModelAlphaMask(al::getSubActor(this, "帽子の的"), al::getModelAlphaMask(this));
    mPlayerHackStartShaderCtrl->update();
    mPlayerHackStartShaderCtrl2->update();
}

// Matching
bool CarryMeat::isFirstDemo() const {
    return true;
}

// Matching
bool CarryMeat::isEnableSkipDemo() const {
    return !mParent->isDropNerve();
}

// Mismatch (nerve address)
void CarryMeat::skipDemo() {
    mParent->skipDemo();
    if (al::isNerve(this, &DemoCarryMeat)) {
        endDemoAndBind(mParent->getBindMtx());
    }
}

// Mismatch (nerve address)
bool CarryMeat::isWaiting() const {
    if (al::isNerve(this, &Wait)) {
        return true;
    }
    return (al::isNerve(this, &WaitSalt));
}

// Mismatch (nerve address) 
bool CarryMeat::isBindable() const {
    return al::isNerve(this, &HackBindable);
}

// mismatch (nerve address)
bool CarryMeat::isCarryReaction() const {
    return al::isNerve(this, &HackBindReaction);
}

// Mismatch (nerve address)
void CarryMeat::drop() {
    _150 = 0;
    al::setNerve(this, &HackFall);
}

// Matching
void CarryMeat::addDemoActor() {
    rs::addDemoActor(al::getSubActor(this, "帽子の的"), false);
}

// Matching
void CarryMeat::exeWaitSalt() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "Wait");
    }
    al::scaleVelocity(this, 0.995);
}

// Mismatch (nerve address)
void CarryMeat::exeHackSalt() {
    if (rs::isTriggerHackAnyButton(mPlayerHack)) {
        al::setNerve(this, &HackSaltJump);
    }
}

// Matching
void CarryMeat::exeHack() {
    al::scaleVelocity(this, 0.995);
}

// Non-matching
void CarryMeat::exeReactionJump() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "ReactionJump");
    }
    u8 _17Fcopy = _17F;
    _17F = 0;

    if (!_17Fcopy && al::isActionEnd(this)) {
        al::setNerve(this, &Wait);
    }
}

// Non-matching
void CarryMeat::exeReactionHipDrop() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "ReactionHipDrop");
    }
    u8 _17Fcopy = _17F;
    _17F = 0;

    if (!_17Fcopy && al::isActionEnd(this)) {
        al::setNerve(this, &Wait);
    }
}

// Matching
void CarryMeat::exeHackBindable() {
    if (al::isFirstStep(this)) {
        al::offCollide(this);
        al::invalidateCollisionParts(this);
        al::tryKillEmitterAndParticleAll(this);
        rs::tryCloseHackTutorial(this);
        al::invalidateClipping(this->mParent);
    }
}

// Matching
void CarryMeat::exeDemoCarryMeat() {
    if (al::isStep(this, 1)) {
        al::resetPosition(this, al::getRailPos(this));
    }
}

// Non-matching (nerve address mismatch)
void CarryMeat::exeHackBind() {
    al::updatePoseMtx(this, _150);
    if (rs::isHoldHackAnyButton(mPlayerHack)) {
        al::setNerve(this, &HackBindReaction);
    }
}

// Non-matching (nerve address mismatch)
void CarryMeat::exeHackBindReaction() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "ReactionCarry");
    }
    al::updatePoseMtx(this, _150);
    if (al::isActionEnd(this)) {
        al::startAction(this, "MoveMeat");
        al::setNerve(this, &HackBind);
    }
}
