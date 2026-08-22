#pragma once

#include "Library/LiveActor/LiveActor.h"

class CarryMeat : public al::LiveActor {
public:
    CarryMeat(const char* name);

    void endDemoAndBind(const sead::Matrix34f*);

    bool isWaiting() const;
    bool isBindable() const;
    bool isCarryReaction() const;

    void startDemo();
    void drop();
    void addDemoActor();

private:
    u64 _108;
    BirdCarryMeat* mBirdCarryMeat;
};
