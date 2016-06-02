#include "Timer.h"
#include "../../include/Nuz/Engine.h"
#include "SceneManager/SceneManager.h"
#include <SDL.h>

using namespace Nuz_;
using namespace Nuz;

Timer::Timer()
{
	Reset();
}


Timer::~Timer()
{
}

uint64_t Nuz_::Timer::GetTime() const
{
	return SDL_GetTicks() - m_begin;
}

void Nuz_::Timer::Reset()
{
	m_begin = SDL_GetTicks();
}

Nuz_::FrameTimer::FrameTimer()
{
	Reset();
}

Nuz_::FrameTimer::~FrameTimer()
{
}

uint64_t Nuz_::FrameTimer::GetTime() const
{
	return ((Nuz_::SceneManager&)Nuz::IEngine::GetGameDevice().GetSceneManager()).GetFrameTime() - m_begin;
}

void Nuz_::FrameTimer::Reset()
{
	m_begin = ((Nuz_::SceneManager&)Nuz::IEngine::GetGameDevice().GetSceneManager()).GetFrameTime();
}

std::shared_ptr<ITimer> Nuz::ITimer::CreateMSTimer()
{
	return std::shared_ptr<ITimer>(new Timer);
}

std::shared_ptr<ITimer> Nuz::ITimer::CreateFrameTimer()
{
	return std::shared_ptr<ITimer>(new FrameTimer);
}
