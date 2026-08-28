#pragma once

#include "Library/HostIO/HioNode.h"

#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>

namespace al {

class RootSercherNode {
public:
    RootSercherNode();

    void clear();
    void open();
    void close();

    int calcTotalCost() const;

private:
    u64 _0 = 0;
    u64 _8 = 0;
    u32 _10 = 0;
    u32 _14 = 0;
    u32 _18 = 0;
    u32 _1C = 0;
    u8 _20 = 0;
    u8 _21 = 0;
};

class RootSercher : public al::HioNode {
public:
    RootSercher();

    void init(int, int);
    void clear();

    RootSercherNode* tryGetNode(int index, int offset) const;
    RootSercherNode* getNode(int arrayIndex, int offset) const;
    void findMinCostOpenNode() const;
    void closeNode(RootSercherNode*, int, int);
    void removeOpenList(RootSercherNode*);
    void openNode(int, int, int, int, RootSercherNode*);
    void isEnableNode(int, int) const;
    void addOpenList(RootSercherNode* node);
    void start(int, int, int, int, int, int);
    void calcNextIndex(int*, int*, int, int) const;

    virtual int calcHeuristicCost(int arg1, int arg2, int arg3, int arg4) const;
    virtual int getConnectCount() const;
    virtual void getConnectIndex(int*, int*, int, int, int) const;

    bool checkReach(int, int) const;
    void calcCost(int, int, RootSercherNode const*) const;
    
private:
    RootSercherNode** mOtherNodeArray = nullptr;
    RootSercherNode** mNodeArray = nullptr;
    s32 _18 = 0;
    s32 _1C = 0;
    s32 mArrayIndex = 0;
    u32 _24 = 0;
    u32 _28 = 0;
    u32 _2C = 0;
    u32 _30 = 0;
    u32 _34 = 0;
    u32 _38 = 0;
    u32 _3C = 0;
};

}   // namespace al