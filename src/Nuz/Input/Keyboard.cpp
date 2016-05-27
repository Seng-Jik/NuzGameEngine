#include "Keyboard.h"
#include <iostream>
using namespace Nuz;

bool Nuz_::Keyboard::KeyPressed(Nuz::KeyCode k) const
{
	return m_kp[(int)k];
}
void Nuz_::Keyboard::DispatchEvent(const SDL_Event & e)
{
	m_changed = true;
	bool kp = e.type == SDL_KEYDOWN;

	switch (e.key.keysym.sym) {

	case SDLK_UP:
		m_kp[(int)KeyCode::Up] = kp; break;
	case SDLK_DOWN:
		m_kp[(int)KeyCode::Down] = kp; break;
	case SDLK_LEFT:
		m_kp[(int)KeyCode::Left] = kp; break;
	case SDLK_RIGHT:
		m_kp[(int)KeyCode::Right] = kp; break;

	case SDLK_LSHIFT:
		m_kp[(int)KeyCode::LShift] = kp; break;
	case SDLK_LCTRL:
		m_kp[(int)KeyCode::LCtrl] = kp; break;
	case SDLK_ESCAPE:
		m_kp[(int)KeyCode::Esc] = kp; break;
	case SDLK_EXECUTE:
		m_kp[(int)KeyCode::Enter] = kp; break;
	case SDLK_F1:
		m_kp[(int)KeyCode::F1] = kp; break;
	case SDLK_F2:
		m_kp[(int)KeyCode::F2] = kp; break;
	case SDLK_F3:
		m_kp[(int)KeyCode::F3] = kp; break;
	case SDLK_F4:
		m_kp[(int)KeyCode::F4] = kp; break;

	case SDLK_z:
		m_kp[(int)KeyCode::Z] = kp; break;
	case SDLK_x:
		m_kp[(int)KeyCode::X] = kp; break;
	}
}

bool Nuz_::Keyboard::Changed()
{
	return m_changed;
}
