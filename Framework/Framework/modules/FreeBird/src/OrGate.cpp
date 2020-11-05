#include "OrGate.h"

namespace freebird
{
    OrGate::OrGate()
        : LogicGate()
    {
    }

    void OrGate::Update()
    {
        if (GetInput1() || GetInput2())
            SetOutput(true);
        else
            SetOutput(false);
    }
}
