#pragma once
#include "../../../include/Nuz/Sound/Sound.h"
#include <map>
#include <mutex>
#include <set>
#include <SDL.h>
#include <SDL_mixer.h>
namespace Nuz_ {
	void channelFinishedHook(int);
	class BgmPlayer;
	class Sound : public Nuz::ISound
	{
	friend class Nuz::ISound;
	friend class BgmPlayer;
	friend void channelFinishedHook(int);
	private:
		static std::mutex m_lock;
		static std::map<std::string, std::weak_ptr<ISound>> m_cache;
		static std::set<int> m_channels;
		static int m_volume;
		Mix_Chunk* m_chunk;
		static int findEmptyChannel();
	public:
		Sound(const std::string&);
		~Sound();
		void Play(int fadein) override;
	};

}