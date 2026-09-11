#include "MapObj/SphinxTaxiWatcher.h"

#include "Library/LiveActor/ActorInitUtil.h"
#include "Library/LiveActor/ActorMovementFunction.h"
#include "Library/LiveActor/ActorPoseUtil.h"
#include "Library/Nerve/NerveSetupUtil.h"
#include "Library/Nerve/NerveUtil.h"
#include "Library/Placement/PlacementFunction.h"

#include "MapObj/TaxiStop.h"
#include "Npc/SphinxRide.h"
#include "System/GameDataFunction.h"
#include "Util/PlayerUtil.h"

namespace {
NERVE_IMPL(SphinxTaxiWatcher, Wait);
NERVE_IMPL(SphinxTaxiWatcher, PlayerBind);

NERVES_MAKE_NOSTRUCT(SphinxTaxiWatcher, Wait, PlayerBind);
}   // namespace

SphinxTaxiWatcher::SphinxTaxiWatcher(const char* name) : al::LiveActor("スフィンクスタクシーの総管理者") {}

void SphinxTaxiWatcher::init(const al::ActorInitInfo& info) {
    al::initActorWithArchiveName(this, info, "SphinxTaxiWatcher", nullptr);
    al::initNerve(this, &Wait, 0);

    s32 numSphinxRides = al::calcLinkChildNum(info, "SphinxRide");
    if (numSphinxRides != 1) {
        makeActorDead();
        return;
    }

    mSphinxRide = new SphinxRide("乗れるスフィンクス");
    al::initLinksActor(mSphinxRide, info, "SphinxRide", 0);

    s32 numTaxiStops = al::calcLinkChildNum(info, "TaxiStop");

    if (numTaxiStops <= 0) {
        makeActorDead();
        return;
    } 

    mTaxiStopArray.allocBuffer(numTaxiStops, nullptr, 8);

    for (s32 i = 0; i != numTaxiStops; i++) {
        TaxiStop* taxiStop = new TaxiStop("タクシー乗り場(呼び出し可能)", mSphinxRide);
        al::initLinksActor(taxiStop, info, "TaxiStop", i);
        mTaxiStopArray.pushBack(taxiStop);
    }

    makeActorAlive();
}

void SphinxTaxiWatcher::initAfterPlacement() {
    u32 w21;
    f32 distToNearestStop; // Distance from mSphinxRide to the nearest TaxiStop

    if (!GameDataFunction::isPayCoinToSphinx(this)) {
        return;
    }

    if (mTaxiStopArray.size() < 1) {
        return;
    }

    distToNearestStop = (al::getTrans(mTaxiStopArray.front()) - rs::getPlayerPos(mSphinxRide)).length();

    if (mTaxiStopArray.size() < 2) {
        w21 = 0;
    }

    else {
        for (int i = 1; i < mTaxiStopArray.size(); i++) {
            f32 distToStop = (al::getTrans(mTaxiStopArray.at(i)) - rs::getPlayerPos(mSphinxRide)).length();
            if (distToNearestStop > distToStop) {
                distToNearestStop = distToStop;
                w21 = i;
            }
        }
    }

    TaxiStop* stop = mTaxiStopArray.at(w21);
    al::resetRotatePosition(mSphinxRide, stop->getRot(), stop->getTrans());
}

void exeWait() {}

void exePlayerWait() {}
