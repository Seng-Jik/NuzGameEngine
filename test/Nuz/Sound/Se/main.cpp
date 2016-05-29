#include "../../../include/Nuz.h"
#include <iostream>
#include <memory>
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
	auto se = ISe::CreateSe("/bgm04.ogg");
	se->Play();
	e.GetSceneManager().Start(sA);
	return 0;
}