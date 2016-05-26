#include "CtxReader.h"
using namespace Nuz_::Renderer;

void CTXReader::OpenBuffer(const void* v)
{
    const char* pc = (const char*)v;
    pc+=4;
    const unsigned short* p = (const unsigned short*)pc;
    m_length = p;
    m_rectNum = m_length + 1;
    m_rectBegin = m_rectNum + 1;
    m_pixels = m_rectBegin + 4**m_rectNum;
}
