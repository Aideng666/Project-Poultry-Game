#include "MeshRenderer.h"
#include <Transform.h>

namespace freebird
{
	MeshRenderer::MeshRenderer(Entity& ent, Mesh& mesh, Shader::sptr& shader)
	{
		thisEnt = &ent;
		thisShader = shader;
		thisMesh = &mesh;
		vao = std::make_unique<VertexArrayObject>();

		MakeVAO(mesh);
	}
	void MeshRenderer::SetMesh(Mesh& mesh)
	{
		thisMesh = &mesh;

		MakeVAO(mesh);
	}
	void MeshRenderer::SetMaterial(Material& mat)
	{
		thisMat = &mat;
	}
	VertexArrayObject::sptr MeshRenderer::MakeVAO(Mesh& mesh)
	{
		vao = VertexArrayObject::Create();

		size_t stride = sizeof(float) * 11;

		vao->AddVertexBuffer(mesh.GetVBO(), {
		BufferAttribute(0, 3, GL_FLOAT, false, stride, NULL, AttribUsage::Position),
		BufferAttribute(1, 3, GL_FLOAT, false, stride, sizeof(float) * 3, AttribUsage::Color),
		BufferAttribute(2, 2, GL_FLOAT, false, stride, sizeof(float) * 6, AttribUsage::Texture),
		BufferAttribute(3, 3, GL_FLOAT, false, stride, sizeof(float) * 8, AttribUsage::Normal)
			});

		return vao;
	}
	void MeshRenderer::Render(Camera& camera, glm::mat4 transform, glm::mat4& lightSpaceMatrix)
	{
		//thisMat->Apply();

		thisShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		thisShader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transform);
		thisShader->SetUniformMatrix("u_Model", transform);
		thisShader->SetUniformMatrix("u_LightSpaceMatrix", lightSpaceMatrix);
		thisShader->SetUniform("u_CamPos", camera.GetPosition());

		vao->Render();
	}

	void MeshRenderer::Render(Shader::sptr& shader, Camera& camera, glm::mat4 transform, glm::mat4& lightSpaceMatrix)
	{
		shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transform);
		shader->SetUniformMatrix("u_Model", transform);
		shader->SetUniformMatrix("u_LightSpaceMatrix", lightSpaceMatrix);
		shader->SetUniform("u_CamPos", camera.GetPosition());

		vao->Render();
	}

	void MeshRenderer::SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 lightCol, float lightAmbientPow, float lightSpecularPow, float lightSpecularPow2, glm::vec3 ambientCol, float ambientPow, float shininess)
	{
		shader->SetUniform("u_LightPos", lightPos);
		shader->SetUniform("u_LightDir", lightDir);
		shader->SetUniform("u_LightCol", lightCol);
		shader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
		shader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
		shader->SetUniform("u_SpecularLightStrength2", lightSpecularPow2);
		shader->SetUniform("u_AmbientCol", ambientCol);
		shader->SetUniform("u_AmbientStrength", ambientPow);
		shader->SetUniform("u_Shininess", shininess);
	}
}
