#include "Sound.h"
#include "../FileSystem/FileSystem.h"
#include "../Engine.h"
#include <SDL_mixer.h>
using namespace Nuz;
using namespace std;
using namespace Nuz_;

std::map<std::string, std::weak_ptr<ISound>> Sound::m_cache;
std::set<int> Sound::m_channels;
int Sound::m_volume = 128;


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

void Nuz::ISound::PauseAllSound()
{
	for (int i : Sound::m_channels)
		if (Mix_Playing(i))
			Mix_Pause(i);
}

void Nuz::ISound::ResumeAllSound()
{
	for (int i : Sound::m_channels)
		if (Mix_Paused(i))
			Mix_Resume(i);
}

void Nuz::ISound::StopAllSound()
{
	for (int i : Sound::m_channels)
		Mix_HaltChannel(i);
	Sound::m_channels.clear();
}

void Nuz::ISound::SetVolumeAllSound(float v)
{
	Sound::m_volume = int(v * 128);
	for (int i : Sound::m_channels) {
		Mix_Volume(i, Sound::m_volume);
	}
}

int Nuz_::Sound::findEmptyChannel()
{
	for (int i = 0; i < 500; ++i) {
		if (!Mix_Playing(i) && !Mix_Paused(i)) {
			return i;
		}
	}
	return -1;
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
	auto channel = findEmptyChannel();
	if (channel == -1) throw std::runtime_error("Cannot play sound,now is playing too much.");
	m_channels.insert(channel);
	Mix_Volume(channel, m_volume);
	Mix_FadeInChannel(channel, m_chunk, 0,fadein);
}

void Nuz_::channelFinishedHook(int channel)
{
	if (Sound::m_channels.count(channel)) Sound::m_channels.erase(channel);
}
