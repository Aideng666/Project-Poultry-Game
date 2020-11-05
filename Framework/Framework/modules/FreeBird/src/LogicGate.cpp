#include "LogicGate.h"

namespace freebird
{
	LogicGate::LogicGate()
	{
		input1 = false;
		input2 = false;
		output = false;
	}

	bool LogicGate::GetInput1()
	{
		return input1;
	}

	bool LogicGate::GetInput2()
	{
		return input2;
	}

	void LogicGate::SetInputs(bool i1, bool i2)
	{
		input1 = i1;
		input2 = i2;
	}

	bool LogicGate::GetOutput()
	{
		return output;
	}

	void LogicGate::SetOutput(bool out)
	{
		output = out;
	}
}
