#include "../../../include/Nuz.h"
#include <iostream>
#include <memory>
#include "../../../src/Nuz/Renderer/OpenGL/glew.h"
#include "../../../src/Nuz/Renderer/OpenGL/Texture.h"
#include "../../../src/Nuz/Renderer/OpenGL/CallList.h"
#include "../../../src/Nuz/Renderer/ImageCacheManager.h"
using namespace std;
using namespace Nuz;

shared_ptr<ICamera2D> pCamera2D;

class Fade :public Nuz::IComponent {
public:
	void OnFadeSwitchInUpdate(float finished) override {
		((ISprite2D*)GetOtherComponent("Hello").get())->SetAlpha(finished);
	};

	void OnFadeSwitchOutUpdate(float finished) override {
		((ISprite2D*)GetOtherComponent("Hello").get())->SetAlpha(1 - finished);
	};

	void OnFadeSwitchIn(int s) override {
		LogStd("Switch Time:" + to_string(s), "NuzTest");
	}
	void OnFadeSwitchOut(int s) override {
		LogStd("Switch Time:"+to_string(s), "NuzTest");
	}
};

int wmain() {
	auto& e = IEngine::GetGameDevice();
	e.GetFileSystem().Mount(e.GetLocalFile());
	AddStdLogWhiteFliter("NuzTest");
	e.SetWindowTitle("Nuz zuN");
	e.SetFPSShowEnable(true);

	try {
		e.InitWindow(400, 300, false);
	}
	catch (Nuz::IShader::ShaderCompileError& e) {
		LogErr(e.what(), "");
	}

	e.BindMessageProcessor(Nuz::IEngine::Message::Quit, []() {
		IEngine::GetGameDevice().GetSceneManager().Exit();
	});

	auto sA = Nuz::IScene::CreateScene();
	auto sB = Nuz::IScene::CreateScene();
	pCamera2D = Nuz::ICamera2D::CreateCamera2D();
	pCamera2D->SetCamera(-8, 4, -8, 4);
	sA->SetCamera2D(pCamera2D);
	sB->SetCamera2D(pCamera2D);

	shared_ptr<IComponent> pA(new Fade), pB(new Fade);

	auto sprite = Nuz::ISprite2D::CreateSprite2D();
	sA->MountComponent(sprite, "Hello");
	sprite->UseImage("/demo.ctx", 0);
	sA->MountComponent(pA);

	sprite = Nuz::ISprite2D::CreateSprite2D();
	sB->MountComponent(sprite, "Hello");
	sprite->UseImage("/demo.ctx", 1);
	sB->MountComponent(pB);

	Nuz::IEngine::GetGameDevice().GetSceneManager().FadeTo(sB, 100);
	Nuz::IEngine::GetGameDevice().GetSceneManager().Start(sA);
	

	return 0;
}