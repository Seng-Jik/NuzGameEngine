#pragma once
#include "../../../../include/Nuz/SceneManager/Components/Shader.h"
#include <map>
#include "../../Renderer/OpenGL/glew.h"
#include "../../Renderer/OpenGL/GLSLProgram.h"
namespace Nuz_ {
	class Shader : public Nuz::IShader
	{
	private:

		struct CreateConfigCompare {
			bool operator ()(const Nuz::IShader::CreateConfig& a, const Nuz::IShader::CreateConfig& b) const {
				if (a.fragmentShader == b.fragmentShader) {
					return a.vertexShader < b.vertexShader;
				}
				else return a.fragmentShader < b.fragmentShader;
			}
		};

		template <class T>
		struct UniformVar {
			int size;
			T var[4];
		};
		static std::map<Nuz::IShader::CreateConfig, std::weak_ptr<Nuz_::Renderer::GLSLProgram>, CreateConfigCompare> m_shaderCache;
		std::map < std::string, UniformVar<float> >  m_uniformsf;
		std::map < std::string, UniformVar<int> >  m_uniformsi;
		std::shared_ptr<Nuz_::Renderer::GLSLProgram> m_shader;
	public:
		Shader(const Nuz::IShader::CreateConfig&);
		void SetUniformFloat(const std::string& uniform,int size, float, float = 0, float = 0, float = 0) override;
		void SetUniformInt(const std::string& uniform, int size, int, int = 0, int = 0, int = 0) override;
		Nuz::IShader::ShaderHandle GetHandle() override;

		void OnDraw2DReady() const override;
		void OnDraw2DFinished() const override;

		void OnDraw3DReady() const override;
		void OnDraw3DFinished() const override;
	};

}