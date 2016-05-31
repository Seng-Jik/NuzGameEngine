#pragma once
#include "glew.h"

namespace Nuz_ {
	namespace Renderer {
		class GLSLProgram
		{
		private:
			GLuint m_handle = 0;
		public:
			GLSLProgram();
			~GLSLProgram();
			void LoadShader(const char* vert, const char* frag);
			inline void Use() { glUseProgram(m_handle); };
			void Clear();
			inline bool Empty() {return m_handle == 0;}
			inline operator GLuint () {return m_handle;}
			inline static void Unuse() { glUseProgram(0); }
		};
	}
}