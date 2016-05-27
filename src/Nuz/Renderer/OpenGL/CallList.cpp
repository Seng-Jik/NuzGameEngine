#include "CallList.h"
#include "../../../../include/Nuz/Engine.h"
using namespace Nuz_::Renderer;

CallList::CallList()
{
	m_callList = glGenLists(1);
	if (m_callList == 0) throw Nuz::IEngine::RendererError("Can not create call list:" + glGetError());
}


CallList::~CallList()
{
	glDeleteLists(m_callList, 1);
}
