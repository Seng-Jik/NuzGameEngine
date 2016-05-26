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
			void DrawToScreen();	//�ѵ�ǰFrameBuffer���Ƶ���ǰ��Ļ��
			void Begin();	//��ʼ���Ƶ�Buffer��
			void End();	//ֹͣ���Ƶ�Buffer��
		};
	}
}
