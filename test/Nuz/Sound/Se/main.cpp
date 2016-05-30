#include "../../../include/Nuz.h"
#include <iostream>
#include <memory>
#include <SDL.h>
using namespace std;
using namespace Nuz;

int wmain() {
	auto& e = IEngine::GetGameDevice();
	e.GetFileSystem().Mount(e.GetLocalFile());
	AddStdLogWhiteFliter("NuzTest");
	e.SetWindowTitle("Nuz zuN");
	e.SetFPSShowEnable(true);

	e.InitWindow(800, 600, false);

	e.BindMessageProcessor(Nuz::IEngine::Message::Quit, []() {
		IEngine::GetGameDevice().GetSceneManager().Exit();
	});
	//e.UnbindMessageProcessor(Nuz::IEngine::Message::Quit);

	e.SetSkipFrame(0);
	auto sA = Nuz::IScene::CreateScene();
	auto bgmPlayer = IBgmPlayer::CreateBgmPlayer();
	auto se = ISound::CreateSound("/th06_04.wav");
	{
		auto se2 = ISound::CreateSound("/th06_05.wav");
		auto se3 = ISound::CreateSound("/th06_04.wav");
		bgmPlayer->SetVolume(0.01);
		bgmPlayer->LoadHeader(se);
		bgmPlayer->LoadLoop(se2);
	}
	
	//se->Play();
	//SDL_Delay(1000);
	bgmPlayer->Play();
	SDL_Delay(4000);
	bgmPlayer->Pause();
	//se->PauseAllSound();
	SDL_Delay(4000);
	bgmPlayer->Resume();
	//se->ResumeAllSound();
	SDL_Delay(4000);
	bgmPlayer->SetVolume(1.0);
	//se->SetVolumeAllSound(0.5);
	e.GetSceneManager().Start(sA);
	return 0;
}