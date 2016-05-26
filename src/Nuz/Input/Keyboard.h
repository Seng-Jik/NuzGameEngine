#pragma once
#include "../../../include/Nuz/Input/Keyboard.h"
#include <SDL.h>

namespace Nuz_ {
	class Keyboard final :public Nuz::IKeyboard {
	private:
		bool m_changed = false;
		bool m_kp[16] = { false };	//注意：只考虑了弹幕游戏
	public:
		bool KeyPressed(Nuz::KeyCode) const override;
		void DispatchEvent(const SDL_Event&);
		bool Changed() override;
		inline void FrameUpdate() {
			m_changed = false;
		}
	};
}