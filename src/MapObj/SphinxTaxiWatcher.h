#pragma once

#include <container/seadPtrArray.h>

#include "Library/LiveActor/LiveActor.h"

class SphinxRide;
class TaxiStop;

class SphinxTaxiWatcher : public al::LiveActor {
public:
    SphinxTaxiWatcher(const char* name);

    void init(const al::ActorInitInfo& info) override;
    void initAfterPlacement() override;

    void exeWait();
    void exePlayerBind();

private:
    SphinxRide* mSphinxRide = nullptr;
    sead::PtrArray<TaxiStop> mTaxiStopArray;
};
