#include "../../../include/Nuz.h"
#include <iostream>
#include <memory>
#include "../../../src/Nuz/Renderer/OpenGL/glew.h"
using namespace std;
using namespace Nuz;

class Prim :public Nuz::IComponent {
public:
	void OnDraw2D() override {
		glClearColor(1.0f, 1.0f, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Unmount() { UnmountSelf(); }
};

class Killer :public Nuz::IComponent {
private:
	int i = 120;
public:
	void OnUpdate() {
		--i;
		if (!i) {
			((Prim*)GetOtherComponent("Hello").get())->Unmount();
		}
	}
};

int main() {
	auto& e = IEngine::GetGameDevice();
	AddStdLogWhiteFliter("Nuz::Renderer");
	e.SetWindowTitle("Nuz zuN");
	e.SetFPSShowEnable(true);
	e.InitWindow(800, 600, false);
	e.SetSkipFrame(0);
	auto sA = Nuz::IScene::CreateScene();
	auto sB = Nuz::IScene::CreateScene();

	auto gA = Nuz::IGameObject::CreateGameObject();
	auto gB = Nuz::IGameObject::CreateGameObject();
	auto pPrim = shared_ptr<IComponent>(new Prim);
	auto pKiller = shared_ptr<IComponent>(new Killer);

	gB->MountComponent(pPrim,"Hello");
	gB->MountComponent(pKiller);
	gA->MountGameObject(gB);

	sB->MountGameObject(gA);
	sA->MountScene(sB);

	e.GetSceneManager().Start(sA);

	return 0;
}