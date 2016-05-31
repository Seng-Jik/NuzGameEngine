#pragma once
#include "../../../../include/Nuz/SceneManager/Components/Shader.h"
namespace Nuz_ {
	class Shader : public Nuz::IShader
	{
	public:
		Shader();
		~Shader();
		/*void SetUniformFloat(const std::string& uniform,int size, float, float = 0, float = 0, float = 0, float = 0) override;
		void SetUniformInt(const std::string& uniform, int size, int, int = 0, int = 0, int = 0, int = 0) override;
		Nuz::IShader::ShaderHandle GetHandle() override;*/
	};

}