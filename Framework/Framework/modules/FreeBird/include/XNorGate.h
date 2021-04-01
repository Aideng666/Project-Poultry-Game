#pragma once
#include "LogicGate.h"

namespace freebird
{
	class XNorGate : public LogicGate
	{
	public:

		XNorGate(Entity ent1, Entity ent2, Entity out);

		void Update();

	private:
	};
}