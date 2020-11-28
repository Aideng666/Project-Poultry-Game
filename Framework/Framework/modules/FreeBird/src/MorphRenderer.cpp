#include "MorphRenderer.h"
#include "Camera.h"

namespace freebird
{
	MorphRenderer::MorphRenderer(Entity& ent, Mesh& base, Shader::sptr& shader/*Material& mat*/)
		: MeshRenderer(ent, base, shader)
	{
		vao = std::make_unique<VertexArrayObject>();

		UpdateData(base, base, 0.0f);
	}
	void MorphRenderer::UpdateData(Mesh& frame0, Mesh& frame1, float t)
	{
		size_t stride = sizeof(float) * 11;

		vao->ClearVertexBuffers();

		vao->AddVertexBuffer(frame0.GetVBO(), {
			BufferAttribute(0, 3, GL_FLOAT, false, stride, NULL, AttribUsage::Position),
			BufferAttribute(1, 3, GL_FLOAT, false, stride, sizeof(float) * 3, AttribUsage::Color),
			BufferAttribute(2, 2, GL_FLOAT, false, stride, sizeof(float) * 6, AttribUsage::Texture),
			BufferAttribute(3, 3, GL_FLOAT, false, stride, sizeof(float) * 8, AttribUsage::Normal)
			});

		vao->AddVertexBuffer(frame1.GetVBO(), {
			BufferAttribute(4, 3, GL_FLOAT, false, stride, NULL, AttribUsage::Position),
			BufferAttribute(5, 3, GL_FLOAT, false, stride, sizeof(float) * 8, AttribUsage::Normal)
			});

		this->t = t;
	}
	void MorphRenderer::Render()
	{
		thisMat->Apply();

		auto& trans = thisEnt->Get<Transform>();

		/*thisScene->GetShader()->SetUniform("MorphT", t);*/

		vao->Render();
	}
}