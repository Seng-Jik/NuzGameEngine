#include "BgmPlayer.h"

using namespace Nuz_;
using namespace Nuz;
using namespace std;
std::map<int, BgmPlayer* > BgmPlayer::m_channel2loop;
std::mutex BgmPlayer::m_lock;
BgmPlayer::BgmPlayer()
{
}


BgmPlayer::~BgmPlayer()
{
	Clear();
}

void Nuz_::BgmPlayer::LoadHeader(const std::shared_ptr<const Nuz::ISound>& head)
{
	if (m_channel != -1) throw std::runtime_error("Dont load bgm when bgm is playing.");
	m_head = head;
}

void Nuz_::BgmPlayer::LoadLoop(const std::shared_ptr<const Nuz::ISound>& loop)
{
	if (m_channel != -1) throw std::runtime_error("Dont load bgm when bgm is playing.");
	m_loop = loop;
}

void Nuz_::BgmPlayer::Clear()
{
	Stop();
	m_head = m_loop = nullptr;
}

void Nuz_::BgmPlayer::Play(int fadein)
{
	if (m_loop == nullptr) throw std::runtime_error("You must load a loop to the bgm player.");
	if (m_channel != -1) throw std::runtime_error("Bgm is playing.");
	m_channel = Sound::findEmptyChannel();
	if (m_channel == -1) throw std::runtime_error("Playing sound is too much.");
	if (m_head == nullptr) Mix_FadeInChannel(m_channel, ((Sound*)m_loop.get())->m_chunk, -1, fadein);
	else {
		lock_guard<mutex> l2(BgmPlayer::m_lock);
		m_channel2loop[m_channel] = this;
		Mix_Volume(m_channel, m_volume);
		Mix_FadeInChannel(m_channel, ((Sound*)m_head.get())->m_chunk, 0, fadein);
	}
}

void Nuz_::BgmPlayer::Pause()
{
	if (m_channel == -1) throw std::runtime_error("Can not pause bgm which is not playing.");
	if (Mix_Paused(m_channel)) throw std::runtime_error("This bgm player is paused.");
	Mix_Pause(m_channel);
}

void Nuz_::BgmPlayer::Resume()
{
	if (m_channel == -1) throw std::runtime_error("Can not pause bgm which is not playing.");
	if (!Mix_Paused(m_channel)) throw std::runtime_error("This bgm player is not paused.");
	Mix_Resume(m_channel);
}

void Nuz_::BgmPlayer::SetVolume(float a)
{
	m_volume = int(128 * a);
	if (m_channel != -1)
		Mix_Volume(m_channel, m_volume);
}

void Nuz_::BgmPlayer::Stop()
{
	if(m_channel == -1) std::runtime_error("Can not stop bgm which is not playing.");
	lock_guard<mutex> l2(BgmPlayer::m_lock);
	if (m_channel2loop.count(m_channel)) m_channel2loop.erase(m_channel);
	Mix_HaltChannel(m_channel);
	m_channel = -1;
}

std::shared_ptr<IBgmPlayer> Nuz::IBgmPlayer::CreateBgmPlayer()
{
	return std::shared_ptr<IBgmPlayer>(new BgmPlayer);
}
