#pragma once

namespace al {

class IEventFlowQueryJudge {
public:
    virtual bool judgeQuery(const char*) = 0;
};

}   // namespace al