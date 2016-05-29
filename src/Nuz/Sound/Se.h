#pragma once
#include "../../../include/Nuz/Sound/Se.h"
#include <queue>
#include <SDL.h>
#include <SDL_mixer.h>
namespace Nuz_ {
	class Se : public Nuz::ISe
	{
	private:
		static std::priority_queue<int> m_channels;
		SDL_RWops* m_rwops;
		std::shared_ptr<std::vector<uint8_t>> m_buffer;
		Mix_Chunk* m_chunk;
	public:
		Se(const std::string&);
		~Se();
		void Play(int fadein) override;
	};

}