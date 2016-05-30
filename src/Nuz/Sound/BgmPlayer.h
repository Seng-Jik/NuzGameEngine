#pragma once
#include "../../../include/Nuz/Sound/BgmPlayer.h"
#include "Sound.h"
#include <mutex>
#include <map>
namespace Nuz_ {
	class BgmPlayer :public Nuz::IBgmPlayer
	{
	friend void channelFinishedHook(int);
	private:
		static std::mutex m_lock;
		static std::map<int, BgmPlayer* > m_channel2loop;	//ͨ��->����ӳ��
		std::shared_ptr<const Nuz::ISound> m_head, m_loop;	//ͷ�Ρ�ѭ����
		int m_volume = 128;
		int m_channel = -1;	//ͨ����������ʱΪ-1��
	public:
		BgmPlayer();
		~BgmPlayer();
		void LoadHeader(const std::shared_ptr<const Nuz::ISound>& head) override;
		void LoadLoop(const std::shared_ptr<const Nuz::ISound>& loop) override;
		void Clear() override;
		void Play(int fadein = 0) override;
		void Pause() override;
		void Resume() override;
		void SetVolume(float) override;
		void Stop() override;
	};

}