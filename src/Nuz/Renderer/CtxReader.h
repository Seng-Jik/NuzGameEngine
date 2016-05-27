#pragma once

namespace Nuz_ {
	namespace Renderer {
		class CTXReader final{
		private:
			const unsigned short* m_length;
			const unsigned short* m_rectNum;
			const unsigned short* m_rectBegin;
			const void* m_pixels;
		public:
			void OpenBuffer(const void*);
			inline unsigned short GetLength() { return *m_length; };
			inline unsigned short GetRectNum() { return *m_rectNum; };
			inline void GetRect(int n, int& x, int& y, int& w, int& h) {
				x = m_rectBegin[4 * n];
				y = m_rectBegin[4 * n + 1];
				w = m_rectBegin[4 * n + 2];
				h = m_rectBegin[4 * n + 3];
			}
			inline const void* GetPixels() { return m_pixels; };
			inline unsigned int GetPixelsSize() { return GetLength()*GetLength() * 4; }
		};
	}
}