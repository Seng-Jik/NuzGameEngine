#pragma once
#include "../../include/Nuz/Font.h"
#include <SDL_ttf.h>

namespace Nuz_ {
	class Font :public Nuz::IFont
	{
	private:
		TTF_Font* m_font;
	public:
		Font(const std::string& file, int size);
		~Font();
		inline operator TTF_Font* () { return m_font; }
	};

}