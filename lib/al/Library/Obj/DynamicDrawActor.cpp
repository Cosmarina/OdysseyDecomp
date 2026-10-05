#include "Library/Obj/DynamicDrawActor.h"

#include "Library/Obj/DynamicMeshDrawer.h"

namespace al {

void DynamicDrawActor::setupHio() {}

void DynamicDrawActor::end() {
    mDynMeshDrawer->end();
}

void DynamicDrawActor::beginModify() {
    mDynMeshDrawer->beginModify();
}

}   // namespace al