#include "AndGate.h"
namespace freebird
{
    AndGate::AndGate()
        : LogicGate()
    {
    }

    void AndGate::Update()
    {
        if (GetInput1() && GetInput2())
            SetOutput(true);
        else
            SetOutput(false);
    }
}
