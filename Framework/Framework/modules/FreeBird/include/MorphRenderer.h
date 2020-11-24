#pragma once

#include <memory>
#include <Entity.h>
#include <Mesh.h>
#include "MeshRenderer.h"

namespace freebird
{
	class MorphRenderer : public MeshRenderer
	{
	public: 

		enum class Attributes
		{
			POS0 = 0,
			POS1 = 1,
			NORM0 = 2,
			NORM1 = 3,
			UV = 4

		};

		MorphRenderer(Entity& ent, Mesh& base, Material& mat, Scene& scene);

		MorphRenderer() = default;

		void UpdateData(const Mesh& frame0, const Mesh& frame1, float t);
		virtual void Draw();

	protected:

		Mesh* frame0, frame1;

		float t;
	};
}