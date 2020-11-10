#include "AndGate.h"

namespace freebird
{
    AndGate::AndGate(Entity ent1, Entity ent2)
        : LogicGate(ent1, ent2)
    {
    }

    void AndGate::Update()
    {
        if (inputEnt1.Has<Wire>() && inputEnt1.Get<Wire>().GetIsPowered() && inputEnt2.Has<Wire>() && inputEnt2.Get<Wire>().GetIsPowered())
            output = true;
        else
            output = false;
    }
}
