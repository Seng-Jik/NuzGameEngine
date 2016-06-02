#include "BufferObject.h"
#include "../../Engine.h"
using namespace Nuz_::Renderer;

GLuint BufferObject::m_utilBuffers[1];
BufferObject::BufferObject()
{
	glGenBuffersARB(1, &m_bufferObject);
	if (m_bufferObject) throw Nuz::IEngine::RendererError("Can not create OpenGL VBO.");
}


BufferObject::~BufferObject()
{
	if (m_bufferObject) glDeleteBuffersARB(1, &m_bufferObject);
}

void Nuz_::Renderer::BufferObject::CreateUtilBuffers()
{
	glGenBuffersARB(1, m_utilBuffers);

	const float vbo0[] = {
		-1,-1,
		1,-1,
		1,1,
		-1,1
	};
	glNamedBufferDataEXT(m_utilBuffers[0], sizeof(vbo0), vbo0, GL_STATIC_DRAW_ARB);

}

void Nuz_::Renderer::BufferObject::DestroyUtilBuffers()
{
	glDeleteBuffers(1, m_utilBuffers);
}

const GLuint Nuz_::Renderer::BufferObject::GetUtilBuffer(int s)
{
	return m_utilBuffers[s];
}

