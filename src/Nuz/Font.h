#pragma once
#include "../../include/Nuz/Font.h"
#include <SDL_ttf.h>
#include <vector>
#include <map>
#include <cstdint>
#include <SDL.h>

namespace Nuz_ {
	class Font :public Nuz::IFont
	{
	friend class Nuz::IFont;
	private:
		static std::map<std::pair<std::string,int>, std::weak_ptr<Nuz::IFont>> m_cache;
		TTF_Font* m_font;
		std::shared_ptr<std::vector<uint8_t>> m_buffer;
		SDL_RWops* m_rwops;
	public:
		Font(const std::string& file, int size);
		~Font();
		inline operator TTF_Font* () { return m_font; }
	};

}