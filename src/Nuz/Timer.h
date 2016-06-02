#pragma once
#include "../../include/Nuz/Timer.h"
namespace Nuz_ {
	class Timer:public Nuz::ITimer
	{
	private:
		uint64_t m_begin;
	public:
		Timer();
		~Timer();
		uint64_t GetTime() const override;
		void Reset() override;
	};

	class FrameTimer :public Nuz::ITimer {
	private:
		uint64_t m_begin;
	public:
		FrameTimer();
		~FrameTimer();
		uint64_t GetTime() const override;
		void Reset() override;
	};
}