#pragma once
#include "PostEffect.h"
#include "LUT.h"

namespace freebird
{
	class ColorCorrection : public PostEffect
	{
	public:
		//Init framebuffer
		//Overrides post effect init
		void Init(unsigned width, unsigned height) override;

		//Applies the effect to this buffer
		//Passes the previous buffer with the texture to apply as a parameter
		void ApplyEffect(PostEffect* buffer) override;

		//applies the effect to the screen

		//Getter
		float GetIntensity() const;
		std::string GetName();

		//Setters
		void SetIntensity(float intensity);
		void SetFilename(std::string name);

	private:

		float _intensity = 1.0f;

		LUT3D testCube;

		std::string filename;
	};
}


