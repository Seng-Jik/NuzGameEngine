#include "Font.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"

Nuz_::Font::Font(const std::string & file, int size)
{
	m_buffer = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(file);
	m_rwops = SDL_RWFromConstMem(&((*m_buffer)[0]), m_buffer->size());
	if (!m_rwops) throw std::runtime_error("Cannot load font rwops:" + std::string(SDL_GetError()));
	m_font = TTF_OpenFontRW(m_rwops, (int)m_buffer->size(), (int)size);
	if (!m_font) throw std::runtime_error("Cannot load font:" + std::string(TTF_GetError()));
}

Nuz_::Font::~Font()
{
	TTF_CloseFont(m_font);
	SDL_FreeRW(m_rwops);
}

std::shared_ptr<Nuz::IFont> Nuz::IFont::CreateFont(const std::string & file, int size)
{
	return std::shared_ptr<IFont>(new Nuz_::Font(file,size));
}
