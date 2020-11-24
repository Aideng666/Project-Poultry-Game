#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Entity.h"
#include "../../../projects/Project Poultry/src/Scene.h"

#include <memory>

namespace freebird
{
	class MeshRenderer
	{
	public:
		MeshRenderer(Entity& ent, Mesh& mesh, Material& mat, Scene& scene);
		MeshRenderer() = default;

		void SetMesh(Mesh& mesh);
		void SetMaterial(Material& mat);
		virtual void Draw();

	protected:
		Entity* thisEnt;
		Material* thisMat;
		Mesh* thisMesh;
		Scene* thisScene;
		std::unique_ptr<VertexArrayObject> vao;
	};

}
