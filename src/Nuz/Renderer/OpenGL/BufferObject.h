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
			/* 获取常用VBO
			 * 0 - 2D下的顶点VBO，存储了一个边长为2的正方形。
			 */
			static const GLuint GetUtilBuffer(int);

			inline void Update(GLenum usage, GLenum target, std::vector<float>& data)
			{
				glNamedBufferDataEXT(m_bufferObject, data.size()*sizeof(float), &data[0], usage);
			}

			//注意：这里传入的vector是完整的vector，不是只修改了部分的vector！
			void Update(GLenum usage, GLenum target, std::vector<float>& data, int begin, int size)
			{
				glNamedBufferSubDataEXT(m_bufferObject, begin, size, &data[begin]);
			}

			inline operator GLuint() const { return m_bufferObject; }
		};
	}
}