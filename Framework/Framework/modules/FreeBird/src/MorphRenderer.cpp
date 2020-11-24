#include "MorphRenderer.h"
#include "Camera.h"

namespace freebird
{
	MorphRenderer::MorphRenderer(Entity& ent, Mesh& base, Material& mat, Scene& scene)
		: MeshRenderer(ent, base, mat, scene)
	{
		thisEnt = &ent;
		thisMat = &mat;
		vao = std::make_unique<VertexArrayObject>();

		UpdateData(base, base, 0.0f);


	}
	void MorphRenderer::UpdateData(const Mesh& frame0, const Mesh& frame1, float t)
	{
		
		//TODO: Complete This Function IDK how
	}
	void MorphRenderer::Draw()
	{
		thisMat->Apply();

		auto& trans = thisEnt->Get<Transform>();

		thisScene->RenderVAO(thisScene->GetShader(), *thisMesh, thisScene->GetCamera().Get<Camera>(), trans.GetModelMatrix());

		thisScene->GetShader()->SetUniform("u_MorphT", t);
	}
}