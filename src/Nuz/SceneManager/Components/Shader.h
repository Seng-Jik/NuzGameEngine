#pragma once
/*#include "../../../../include/Nuz/SceneManager/Components/Shader.h"
#include <map>
#include "../../Renderer/OpenGL/glew.h"
namespace Nuz_ {
	class Shader : public Nuz::IShader
	{
	private:
		struct UniformVar {
			int size;
			float var[4];
		};
		static std::map<std::pair<std::string, std::string>, GLuint> m_shaders;
		std::map < std::string, UniformVar>  m_uniforms;
	public:
		Shader(const char* vert, const char* frag);
		~Shader();
		void SetUniformFloat(const std::string& uniform,int size, float, float = 0, float = 0, float = 0, float = 0) override;
		void SetUniformInt(const std::string& uniform, int size, int, int = 0, int = 0, int = 0, int = 0) override;
		Nuz::IShader::ShaderHandle GetHandle() override;
	};

}*/