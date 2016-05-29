#pragma once
#include "glew.h"
#include <string>
#include <cstdint>
#include <vector>
#include <SDL.h>
namespace Nuz_ {
	namespace Renderer {
		class Texture final
		{
		public:
			struct UVRect {
				float x, y, w, h;
			};
		private:

			GLuint m_texture = 0;
			std::vector<UVRect> m_rects;
			uint16_t m_w=0,m_h=0;

			
		public:
			Texture();
			~Texture();
			inline operator GLuint () { return m_texture; }
			void LoadImage(const std::string& path);
			void LoadSurface(SDL_Surface*);
			inline UVRect GetUVRect(uint8_t num) const { return m_rects.at(num); }
			inline void GetSize(int& w, int& h) { w = m_w; h = m_h; }
			void Clear();
			inline void Bind() { glBindTexture(GL_TEXTURE_2D, m_texture); }
			inline static void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
		};
	}
}
