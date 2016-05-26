#include "InputDevice.h"

Nuz::IKeyboard & Nuz_::InputDeviceManager::GetKeyboard()
{
	return m_keyboard;
}

void Nuz_::InputDeviceManager::DispatchEvent(const SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) m_keyboard.DispatchEvent(e);
}

void Nuz_::InputDeviceManager::FrameUpdate()
{
	m_keyboard.FrameUpdate();
}
