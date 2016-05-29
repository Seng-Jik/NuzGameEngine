#include "Font.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"

Nuz_::Font::Font(const std::string & file, int size)
{
	auto buffer = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(file);
	auto rwops = SDL_RWFromMem((char*)&(*buffer)[0], buffer->size());
	m_font = TTF_OpenFontRW(rwops, (int)buffer->size(), (int)size);
	if (!m_font) throw std::runtime_error("Cannot load font:" + std::string(TTF_GetError()));
	SDL_RWclose(rwops);
}

Nuz_::Font::~Font()
{
	TTF_CloseFont(m_font);
}

std::shared_ptr<Nuz::IFont> Nuz::IFont::CreateFont(const std::string & file, int size)
{
	return std::shared_ptr<IFont>(new Nuz_::Font(file,size));
}
