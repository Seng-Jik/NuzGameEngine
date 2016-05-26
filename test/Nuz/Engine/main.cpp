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
	shared_ptr<Nuz_::Renderer::Texture> m_texture;
	Nuz_::Renderer::ImageCacheManager m_imc;
	Nuz_::Renderer::CallList m_cl;
public:
	Prim() {
		m_texture = m_imc.LoadImage("/demo.ctx");
		m_cl.DefineBegin();
		glBegin(GL_QUADS); {
			glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, -1.0);

			glTexCoord2f(1.0, 1.0); glVertex2f(1.0, -1.0);

			glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 1.0);

			glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, 1.0);

		}
		glEnd();
		m_cl.DefineEnd();
	}
	void OnDraw2D() override {
		//glEnable(GL_TEXTURE_2D);
		m_texture->Bind();
		m_cl();
		m_texture->Unbind();
	}
	void OnUpdate() override {
		if (IEngine::GetGameDevice().GetInputDeviceManager().GetKeyboard().KeyPressed(KeyCode::Up)) {
			pCamera2D->Move(0, 0.01);
		}
		if (IEngine::GetGameDevice().GetInputDeviceManager().GetKeyboard().KeyPressed(KeyCode::Down)) {
			pCamera2D->Move(0, -0.01);
		}
		if (IEngine::GetGameDevice().GetInputDeviceManager().GetKeyboard().KeyPressed(KeyCode::Left)) {
			pCamera2D->Move(-0.01, 0);
		}
		if (IEngine::GetGameDevice().GetInputDeviceManager().GetKeyboard().KeyPressed(KeyCode::Right)) {
			pCamera2D->Move(0.01, 0);
		}
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
	e.GetFileSystem().Mount(e.GetLocalFile());
	//AddStdLogWhiteFliter("Nuz::Renderer");
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
	{
		auto sB = Nuz::IScene::CreateScene();

		auto gA = Nuz::IGameObject::CreateGameObject();
		auto gB = Nuz::IGameObject::CreateGameObject();
		auto pPrim = shared_ptr<IComponent>(new Prim);
		auto pKiller = shared_ptr<IComponent>(new Killer);

		pCamera2D = Nuz::ICamera2D::CreateCamera2D();
		pCamera2D->SetCamera(-1, 1, -1, 1, 0, 100);
		sA->SetCamera2D(pCamera2D);

		gB->MountComponent(pPrim, "Hello");
		//gB->MountComponent(pKiller);
		gA->MountGameObject(gB);

		sB->MountGameObject(gA);
		sA->MountScene(sB);
	}

	e.GetSceneManager().Start(sA);

	return 0;
}