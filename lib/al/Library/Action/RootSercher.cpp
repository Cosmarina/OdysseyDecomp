#include "Library/Action/RootSercher.h"

namespace al {
    
RootSercherNode::RootSercherNode() {}

void RootSercherNode::clear() {
    _0 = 0;
    _8 = 0;
    _18 = 0;
    _1C = 0;
    _20 = 0;
    _21 = 0;
}

void RootSercherNode::open() {
    _20 = 1;
}

void RootSercherNode::close() {
    _20 = 2;
}

int RootSercherNode::calcTotalCost() const {
    return _18 + _1C;
}

RootSercher::RootSercher() {}

// TODO: Match function
void RootSercher::init(int, int) {

}

// TODO: Match function
void RootSercher::clear() {

}

// TODO: Match function
RootSercherNode* RootSercher::tryGetNode(int index, int offset) const {
    RootSercherNode* node = nullptr;
    if (index > -1 && offset > -1 && index < _18) {
        if (_1C <= offset) {
            return nullptr; 
        }
        node = mOtherNodeArray[index] + offset;
    }
    return node;
}

RootSercherNode* RootSercher::getNode(int arrayIndex, int offset) const {
    RootSercherNode* node = mOtherNodeArray[arrayIndex];
    return offset + node;
}

// TODO: Match function
void RootSercher::findMinCostOpenNode() const {

}

// TODO: Match function
void RootSercher::closeNode(RootSercherNode*, int, int) {

}

// TODO: Match function
void RootSercher::removeOpenList(RootSercherNode*) {

}

// TODO: Match function
void RootSercher::openNode(int, int, int, int, RootSercherNode*) {

}

// TODO: Match function
void RootSercher::isEnableNode(int, int) const {

}

void RootSercher::addOpenList(RootSercherNode* node) {
    mNodeArray[mArrayIndex] = node;
    mArrayIndex++;
}

// TODO: Match function
void RootSercher::start(int, int, int, int, int, int) {

}

// TODO: Match function
void RootSercher::calcNextIndex(int*, int*, int, int) const {

}

int RootSercher::calcHeuristicCost(int arg1, int arg2, int arg3, int arg4) const {
    int mag1 = sead::Mathi::abs(arg3 - arg1);
    int mag2 = sead::Mathi::abs(arg4 - arg2);
    // I have no idea what this math is meant to do
    return ((mag1 == 0 || mag2 == 0) | (mag1 + mag2) * 2) ^ 1;
}

int RootSercher::getConnectCount() const { return 4; }

// TODO: Match function
void RootSercher::getConnectIndex(int*, int*, int, int, int) const {

}

bool RootSercher::checkReach(int, int) const { return true; }

// TODO: Match function
void RootSercher::calcCost(int, int, RootSercherNode const*) const {

}

}   // namespace al