#pragma once
#include "../../../include/Nuz/Input/InputDeviceManager.h"
#include "Keyboard.h"
#include <SDL.h>

namespace Nuz_ {
	class InputDeviceManager final :public Nuz::IInputDeviceManager {
	private:
		Keyboard m_keyboard;
	public:
		Nuz::IKeyboard& GetKeyboard() override;
		void DispatchEvent(const SDL_Event&);
		void FrameUpdate();
	};
}