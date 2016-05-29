#include "Se.h"
#include "../FileSystem/FileSystem.h"
#include "../Engine.h"
#include <SDL_mixer.h>
using namespace Nuz;
using namespace std;
using namespace Nuz_;

std::shared_ptr<ISe> Nuz::ISe::CreateSe(const std::string & s)
{
	return std::shared_ptr<ISe>(new Nuz_::Se(s));
}

Nuz_::Se::Se(const std::string & path)
{
	m_buffer = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(path);
	m_rwops = SDL_RWFromConstMem(&((*m_buffer)[0]), m_buffer->size());
	if (!m_rwops) throw std::runtime_error(string("Cannnot create rwops from file:") + SDL_GetError());
	m_chunk = Mix_LoadWAV_RW(m_rwops, m_buffer->size());
	if (!m_chunk) throw std::runtime_error(string("Cannot load se:") + Mix_GetError());
}

Nuz_::Se::~Se()
{
	Mix_FreeChunk(m_chunk);
	SDL_FreeRW(m_rwops);
}

void Nuz_::Se::Play(int fadein)
{
	Mix_FadeInChannel(-1, m_chunk, 0,fadein);
}
