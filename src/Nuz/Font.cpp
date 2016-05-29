#include "Font.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"

Nuz_::Font::Font(const std::string & file, int size)
{
	auto buffer = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(file);
	auto rwops = SDL_RWFromMem((char*)&(*buffer)[0], buffer->size());
	m_font = TTF_OpenFontRW(rwops, (int)buffer->size(), (int)size);
	SDL_RWclose(rwops);
}

Nuz_::Font::~Font()
{
	TTF_CloseFont(m_font);
}
