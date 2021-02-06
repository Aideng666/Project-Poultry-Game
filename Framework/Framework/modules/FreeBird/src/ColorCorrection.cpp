#include "ColorCorrection.h"
namespace freebird
{
	void ColorCorrection::Init(unsigned width, unsigned height)
	{
		int index = int(_buffers.size());

		if (!_shaders.size() > 0)
		{
			_buffers.push_back(new Framebuffer());
			_buffers[index]->AddColorTarget(GL_RGBA8);
			_buffers[index]->AddDepthTarget();
			_buffers[index]->Init(width, height);
		}
		//Loads the shaders
		 index = int(_shaders.size());
		_shaders.push_back(Shader::Create());
		_shaders[index]->LoadShaderPartFromFile("Shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
		_shaders[index]->LoadShaderPartFromFile("Shaders/color_correction_frag.glsl", GL_FRAGMENT_SHADER);
		_shaders[index]->Link();

		PostEffect::Init(width, height);

		testCube.loadFromFile(filename);
	}

	void ColorCorrection::ApplyEffect(PostEffect* buffer)
	{
		BindShader(0);
		_shaders[0]->SetUniform("u_Intensity", _intensity);

		buffer->BindColorAsTexture(0, 0, 0);

		testCube.bind(30);

		_buffers[0]->RenderToFSQ();

		//_buffers[0]->DrawFullscreenQuad();

		testCube.unbind(30);

		buffer->UnbindTexture(0);

		UnbindShader();
	}

	float ColorCorrection::GetIntensity() const
	{
		return _intensity;
	}

	std::string ColorCorrection::GetName()
	{
		return filename;
	}

	void ColorCorrection::SetIntensity(float intensity)
	{
		_intensity = intensity;
	}
	void ColorCorrection::SetFilename(std::string name)
	{
		filename = name;
	}
}
