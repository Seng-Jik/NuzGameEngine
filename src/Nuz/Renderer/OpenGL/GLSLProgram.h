#pragma once
#include "glew.h"
#include "../../../../include/Nuz/SceneManager/Components/Shader.h"
#include <map>
#include <string>
namespace Nuz_ {
	namespace Renderer {
		class GLSLProgram
		{
		private:

			class GLSLShader {
			private:
				GLenum m_type;
				GLuint m_shader = 0;
			public:
				void CompileShader(const char* source,GLenum type);
				inline operator GLuint() { return m_shader; }
				~GLSLShader();
			};

			static GLSLShader m_normalVertShader, m_normalFragShader;
			static GLuint m_normalShaderProgram;	//πÃ∂®π‹œﬂ£®Œ±

			GLuint m_program = 0;
		public:
			GLSLProgram();
			~GLSLProgram();
			static void CompileNormalShaders();
			static void DestroyNormalShaders();
			void LoadShader(const Nuz::IShader::CreateConfig& c);
			inline void Use() const { glUseProgram(m_program); };
			void Clear();
			inline bool Empty() const {return m_program == 0;}
			inline operator GLuint () {return m_program;}
			inline static void Unuse() { glUseProgram(m_normalShaderProgram); }
		};
	}
}