#pragma once

namespace freebird
{
	class LogicGate
	{
	public:

		LogicGate();

		virtual void Update() {}

		//SETTERS
		void SetInputs(bool i1, bool i2);
		void SetOutput(bool out);

		//GETTERS
		bool GetInput1();
		bool GetInput2();
		bool GetOutput();

	private:

		bool input1, input2, output;
	};
}

