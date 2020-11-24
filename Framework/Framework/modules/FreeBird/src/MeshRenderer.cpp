#include "MeshRenderer.h"
#include <Transform.h>

namespace freebird
{
	MeshRenderer::MeshRenderer(Entity& ent, Mesh& mesh, Material& mat, Scene& scene)
	{
		thisEnt = &ent;
		thisMat = &mat;
		thisMesh = &mesh;
		thisScene = &scene;
		vao = std::make_unique<VertexArrayObject>();
	}
	void MeshRenderer::SetMesh(Mesh& mesh)
	{
		thisMesh = &mesh;
	}
	void MeshRenderer::SetMaterial(Material& mat)
	{
		thisMat = &mat;
	}
	void MeshRenderer::Draw()
	{
		thisMat->Apply();

		auto& trans = thisEnt->Get<Transform>();

		thisScene->RenderVAO(thisScene->GetShader(), *thisMesh, thisScene->GetCamera().Get<Camera>(), trans.GetModelMatrix());
	}
}
