#include "Font.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"
using namespace Nuz_;
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
	std::pair<std::string, int> s;
	s.first = file;
	s.second = size;
	if (Font::m_cache.count(s)) {
		if (!Font::m_cache.at(s).expired()) {
			return Font::m_cache.at(s).lock();
		}
	}
	auto p = std::shared_ptr<IFont>(new Nuz_::Font(file,size));
	Font::m_cache[s] = p;
	return p;
}
std::map<std::pair<std::string, int>, std::weak_ptr<Nuz::IFont>> Font::m_cache;