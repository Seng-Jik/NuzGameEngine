#pragma once
#include "../../../include/Nuz/Sound/Sound.h"
#include <map>
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
namespace Nuz_ {
	class Sound : public Nuz::ISound
	{
	friend class Nuz::ISound;
	private:
		static std::map<std::string, std::weak_ptr<ISound>> m_cache;
		Mix_Chunk* m_chunk;
	public:
		Sound(const std::string&);
		~Sound();
		void Play(int fadein) override;
	};

}