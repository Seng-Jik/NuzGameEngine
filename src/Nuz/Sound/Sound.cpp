#include "Sound.h"
#include "../FileSystem/FileSystem.h"
#include "../Engine.h"
#include <SDL_mixer.h>
using namespace Nuz;
using namespace std;
using namespace Nuz_;

std::map<std::string, std::weak_ptr<ISound>> Sound::m_cache;

std::shared_ptr<ISound> Nuz::ISound::CreateSound(const std::string & s)
{
	if (Sound::m_cache.count(s)) {
		if (!Sound::m_cache.at(s).expired()) {
			return Sound::m_cache.at(s).lock();
		}
	}
	auto p = std::shared_ptr<ISound>(new Nuz_::Sound(s));
	Sound::m_cache[s] = p;
	return p;
}

Nuz_::Sound::Sound(const std::string & path)
{
	auto m_buffer = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(path);
	auto m_rwops = SDL_RWFromConstMem(&((*m_buffer)[0]), m_buffer->size());
	if (!m_rwops) throw std::runtime_error(string("Cannnot create rwops from file:") + SDL_GetError());
	m_chunk = Mix_LoadWAV_RW(m_rwops, m_buffer->size());
	if (!m_chunk) throw std::runtime_error(string("Cannot load se:") + Mix_GetError());
	SDL_FreeRW(m_rwops);
}

Nuz_::Sound::~Sound()
{
	Mix_FreeChunk(m_chunk);
}

void Nuz_::Sound::Play(int fadein)
{
	Mix_FadeInChannel(-1, m_chunk, 0,fadein);
}
