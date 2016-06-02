#pragma once
#pragma once
#include "glew.h"
#include <vector>

namespace Nuz_ {
	namespace Renderer {
		class BufferObject
		{
		private:
			static GLuint m_utilBuffers[1];
			GLuint m_bufferObject;
		public:
			BufferObject();
			~BufferObject();

			static void CreateUtilBuffers();
			static void DestroyUtilBuffers();
			/* ��ȡ����VBO
			 * 0 - 2D�µĶ���VBO���洢��һ���߳�Ϊ2�������Ρ�
			 */
			static const GLuint GetUtilBuffer(int);

			inline void Update(GLenum usage, GLenum target, std::vector<float>& data)
			{
				glNamedBufferDataEXT(m_bufferObject, data.size()*sizeof(float), &data[0], usage);
			}

			//ע�⣺���ﴫ���vector��������vector������ֻ�޸��˲��ֵ�vector��
			void Update(GLenum usage, GLenum target, std::vector<float>& data, int begin, int size)
			{
				glNamedBufferSubDataEXT(m_bufferObject, begin, size, &data[begin]);
			}

			inline operator GLuint() const { return m_bufferObject; }
		};
	}
}