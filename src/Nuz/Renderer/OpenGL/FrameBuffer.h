#pragma once
#include "glew.h"

namespace Nuz_ {
	namespace Renderer {
		class FrameBuffer final
		{
		private:
			GLuint m_frameBuffer;

			GLuint m_depthBuffer, m_renderBufferTexture;

		public:
			FrameBuffer();
			~FrameBuffer();
			void DrawToScreen();	//把当前FrameBuffer绘制到当前屏幕上
			void Begin();	//开始绘制到Buffer上
			void End();	//停止绘制到Buffer上
		};
	}
}
