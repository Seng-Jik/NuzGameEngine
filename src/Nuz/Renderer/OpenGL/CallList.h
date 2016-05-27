#pragma once
#include "glew.h"

namespace Nuz_ {
	namespace Renderer {
		class CallList final
		{
		private:
			GLuint m_callList;
		public:
			CallList();
			~CallList();
			inline void DefineBegin(){ glNewList(m_callList, GL_COMPILE); }
			inline void DefineEnd() { glEndList(); }
			inline void operator()() const { glCallList(m_callList); }
		};
	}
}