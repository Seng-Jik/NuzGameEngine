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

class Prim :public Nuz::IComponent {
private:
	float x=-2, y=2, w=100, h=60;
	float scl_w = 0.5f, scl_h = 1.0f;
	float angle = 0.0f;
public:
	Prim() {
	}
	void OnUpdate(bool& draw2D,bool& draw3D) override {
		shared_ptr<IComponent> m_hello = GetOtherComponent("Hello");
		//((ISprite2D*)m_hello.get())->SetPos(x, y);
		//((ISprite2D*)m_hello.get())->SetRotate(true, 1, 1, angle, true, false);
		//((ISprite2D*)m_hello.get())->SetScale(scl_w, scl_h);
		auto& key = Nuz::IEngine::GetGameDevice().GetInputDeviceManager().GetKeyboard();
		if (key.KeyPressed(KeyCode::Down)) y -= 0.003f;
		if (key.KeyPressed(KeyCode::Up)) y += 0.003f;
		if (key.KeyPressed(KeyCode::Left)) x -= 0.003f;
		if (key.KeyPressed(KeyCode::Right)) x += 0.003f;
		if (key.KeyPressed(KeyCode::Z)) angle += 1.0f; 
		if (key.KeyPressed(KeyCode::LShift)) scl_w += 0.01f;
		if (key.KeyPressed(KeyCode::X)) scl_h += 0.01f;
		if (key.KeyPressed(KeyCode::Esc)) ((ISprite2D*)m_hello.get())->SetDstSizeAsDefault();

	}
	void Unmount() { UnmountSelf(); }
};
/*
class Killer :public Nuz::ILogic {
private:
	int i = 120;
public:
	bool OnUpdate() {
		--i;
		if (!i) {
			((Prim*)GetOtherComponent("Hello").get())->Unmount();
		}
		return false;
	}
};
*/
int wmain(){
	auto& e = IEngine::GetGameDevice();
	e.GetFileSystem().Mount(e.GetLocalFile());
	//AddStdLogWhiteFliter("Nuz::Renderer");
	AddStdLogWhiteFliter("NuzTest");
	e.SetWindowTitle("Nuz zuN");
	e.SetFPSShowEnable(true);

	e.InitWindow(400, 300, false);
	
	e.BindMessageProcessor(Nuz::IEngine::Message::Quit, []() {
		IEngine::GetGameDevice().GetSceneManager().Exit();
	});
	//e.UnbindMessageProcessor(Nuz::IEngine::Message::Quit);

	e.SetSkipFrame(0); 
	auto sA = Nuz::IScene::CreateScene();
	pCamera2D = Nuz::ICamera2D::CreateCamera2D();
	pCamera2D->SetCamera(-8, 8, -8, 8);
	sA->SetCamera2D(pCamera2D);

	auto sprite = Nuz::ISprite2D::CreateSprite2D();
	sA->MountComponent(sprite,"Hello");
	auto pPrim = shared_ptr<IComponent>(new Prim);
	sA->MountComponent(pPrim);
	sprite->UseImage("/demo.ctx", 0);
	sprite->SetAlpha(0.5);
	sprite->SetColorFliter(0.5, 0.5, 1.0);
	
	auto font = IFont::CreateFont("/test.ttf", 32);
	auto font2 = IFont::CreateFont("/test.ttf", 32);
	auto font3 = IFont::CreateFont("/test.ttf", 64);
	sprite->UseText(*font, L"HelloWorld",0,255,0);
	
	//sprite->UseText()

	/*{
		auto sB = Nuz::IScene::CreateScene();

		auto gA = Nuz::IGameObject::CreateGameObject();
		auto gB = Nuz::IGameObject::CreateGameObject();
		auto pPrim = shared_ptr<IComponent>(new Prim);
		auto pKiller = shared_ptr<IComponent>(new Killer);

		
		pCamera2D->SetCamera(-1, 1, -1, 1);
		sA->SetCamera2D(pCamera2D);

		gB->MountComponent(pPrim, "Hello");
		//gB->MountComponent(pKiller);
		gA->MountGameObject(gB);

		sB->MountGameObject(gA);
		sA->MountScene(sB);
	}*/

	e.GetSceneManager().Start(sA);

	return 0;
}