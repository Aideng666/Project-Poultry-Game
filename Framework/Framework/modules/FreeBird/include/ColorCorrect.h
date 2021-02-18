#pragma once

#include "PostEffect.h"
#include "LUT.h"

namespace freebird
{
	class ColorCorrect : public PostEffect
	{
	public:
		//Initializes framebuffer
		//Overrides post effect Init
		void Init(unsigned width, unsigned height) override;

		//Applies the effect to this buffer
		//passes the previous framebuffer with the texture to apply as parameter
		void ApplyEffect(PostEffect* buffer) override;

		//Getters
		LUT3D GetLUT() const;

		//Setters
		void SetLUT(LUT3D cube);
	private:
		LUT3D _Lut;
	};
}