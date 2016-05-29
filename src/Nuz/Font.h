#pragma once
#include "../../include/Nuz/Font.h"
#include <SDL_ttf.h>
#include <vector>
#include <cstdint>
#include <SDL.h>

namespace Nuz_ {
	class Font :public Nuz::IFont
	{
	private:
		TTF_Font* m_font;
		std::shared_ptr<std::vector<uint8_t>> m_buffer;
		SDL_RWops* m_rwops;
	public:
		Font(const std::string& file, int size);
		~Font();
		inline operator TTF_Font* () { return m_font; }
	};

}