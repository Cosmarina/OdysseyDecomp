#include "MapObj/CapSlotReel.h"

#include "Library/Item/ItemUtil.h"
#include "Library/LiveActor/ActorActionFunction.h"
#include "Library/LiveActor/ActorAnimFunction.h"
#include "Library/LiveActor/ActorFlagFunction.h"
#include "Library/LiveActor/ActorPoseUtil.h"
#include "Library/LiveActor/ActorSensorUtil.h"
#include "Library/Math/MathUtil.h"
#include "Library/Nerve/NerveSetupUtil.h"
#include "Library/Nerve/NerveUtil.h"

#include "Util/PlayerUtil.h"
#include "Util/SensorMsgFunction.h"

namespace {
NERVE_HOST_TYPE_IMPL(CapSlotReel, MoveStart);
NERVE_HOST_TYPE_IMPL(CapSlotReel, Stop);
NERVE_HOST_TYPE_IMPL(CapSlotReel, Hit);
NERVE_HOST_TYPE_IMPL(CapSlotReel, Move);

NERVES_MAKE_STRUCT(HostType, MoveStart, Stop, Hit, Move);
}   // namespace

CapSlotReel::CapSlotReel(const char* name, al::LiveActor* actor1, al::LiveActor* actor2) : al::LiveActor(name) {
    mActor = actor1;
    mActor2 = actor2;
}

void CapSlotReel::init(const al::ActorInitInfo& info) {

}

// MATCHING
void CapSlotReel::appear() {
    al::LiveActor::appear();
    _130 = 0;
    al::startAction(mActor2, "WaitStart");
    al::setNerve(this, &NrvHostType.MoveStart);
}

void CapSlotReel::getItemType() const {

}

// MATCHING
bool CapSlotReel::isStopped() const {
    return al::isNerve(this, &NrvHostType.MoveStart);
}

// MATCHING
bool CapSlotReel::isDecidedItem() const {
    if (al::isNerve(this, &NrvHostType.Stop)) {
        return true;
    }
    return al::isNerve(this, &NrvHostType.MoveStart);
}

// MATCHING
bool CapSlotReel::isCapHit(const al::SensorMsg* message, al::HitSensor* other, al::HitSensor* self) const {
    if (al::isMySensor(self, this) && rs::isMsgCapAttack(message)) {
        return rs::isPlayerCapFlying(this);
    }
    return false;
}

// MATCHING
bool CapSlotReel::receiveMsg(const al::SensorMsg* message, al::HitSensor* other, al::HitSensor* self) {
    if (rs::isMsgPlayerDisregardTargetMarker(message)) {
        return true;
    }

    if (al::isNerve(this, &NrvHostType.Hit) && al::isGreaterStep(this, 0)) {
        if (al::isMySensor(self, this) && rs::isMsgCapAttack(message) && rs::isPlayerCapFlying(this)) {
            al::setAppearItemAttackerSensor(mActor, other);
            al::setNerve(this, &NrvHostType.Stop);
        } 
    }
    else if (al::isMsgPlayerDisregard(message) || rs::isMsgPlayerDisregardHomingAttack(message)) {
        return true;
    }
    return false;
}

// MATCHING
void CapSlotReel::reset() {
    al::startAction(mActor2, "Wait");
}

// MATCHING
void CapSlotReel::updatePose() {
    if (mPoseMtx) {
        al::updatePoseMtx(this, mPoseMtx);
    }
}

// MATCHING
void CapSlotReel::exeMoveStart() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "Move");
        al::setSklAnimFrameRate(this, mAnimFrameRate, 0);
    }
    
    if (al::isActionEnd(this)) {
        al::setNerve(this, &NrvHostType.Hit);
    }
}

// NON-MATCHING
void CapSlotReel::exeMove() {
    if (al::isFirstStep(this)) {
        al::tryStartActionIfNotPlaying(this, "Move");
        _130 = al::wrapValue(_130 + 1, mArrayLength);
        al::setSklAnimFrameRate(this, mAnimFrameRate, 0);

        if (0 < mArrayLength) {
            s32 i = 0;
            do {
                LiveActor* actor;
                if (i < mArrayLength) {
                    actor = mActorArray[i];
                }
                else {
                    actor = nullptr;
                }

                if (i == _130) {
                    if (!al::isAlive(actor)) {
                        actor->appear();
                    }
                }
                else if (!al::isDead(actor)) {
                    actor->kill();
                }
                i++;
            } while (i < mArrayLength);
        }
        
    }

    if (al::isActionEnd(this)) {
        al::startAction(this, "Move");
        al::setNerve(this, &NrvHostType.Hit);
    }
}

// MATCHING
void CapSlotReel::exeHit() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "Hit");
        al::startAction(mActor2, "WaitStop");
    }
    
    if (al::isActionEnd(this)) {
        al::setNerve(this, &NrvHostType.MoveStart);
    }
}

// MATCHING
void CapSlotReel::exeStop() {}