#pragma once
#include "glew.h"
#include "../../../../include/Nuz/SceneManager/Components/Shader.h"
namespace Nuz_ {
	namespace Renderer {
		class GLSLProgram
		{
		private:
			GLuint m_handle = 0;
		public:
			GLSLProgram();
			~GLSLProgram();
			void LoadShader(const Nuz::IShader::CreateConfig& c);
			inline void Use() const { glUseProgram(m_handle); };
			void Clear();
			inline bool Empty() const {return m_handle == 0;}
			inline operator GLuint () {return m_handle;}
			inline static void Unuse() { glUseProgram(0); }
		};
	}
}