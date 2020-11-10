#include "OrGate.h"

namespace freebird
{
    OrGate::OrGate(Entity ent1, Entity ent2)
        : LogicGate(ent1, ent2)
    {
    }

    void OrGate::Update()
    {
        if (input1 || input2)
            output = true;
        else
            output = false;
    }
}
