#include "SceneManager.h"
#include "Scene.h"
#include "../Engine.h"
#include <set>
#include "DrawTask.h"
#include "GameObjectFloder.h"
#include "Camera2D.h"
//#include "Camera3D.h"
#include <SDL.h>
#include "../Renderer/OpenGL/glew.h"

using namespace Nuz_;
using namespace std;

/* 精准FPS控制，返回值为FPS值 */
static float waitFps(int FPS) {
	static int fps_count = 0, count0t;
	static int f[60];
	static float ave;

	{
		int term, i, gnt;
		static int t = 0;
		if (fps_count == 0) {
			if (t == 0)
				term = 0;
			else
				term = count0t + 1000 - SDL_GetTicks();
		}
		else
			term = (int)(count0t + fps_count*(1000.0 / FPS)) - SDL_GetTicks();

		if (term>0)
			SDL_Delay(term);

		gnt = SDL_GetTicks();

		if (fps_count == 0)
			count0t = gnt;
		f[fps_count] = gnt - t;
		t = gnt;
		if (fps_count == FPS - 1) {
			ave = 0;
			for (i = 0; i<FPS; i++)
				ave += f[i];
			ave /= FPS;
		}
		++fps_count;
		fps_count = fps_count%FPS;
	}
	return 1000.0f / ave;
}


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void Nuz_::SceneManager::Start(std::shared_ptr<Nuz::IScene> p)
{
	m_mainLoop = true;
	static vector<DrawTask2D> drawTask2D;
	static vector<DrawTask3D> drawTask3D;
	Nuz_::Scene* now = (Nuz_::Scene*)p.get();
	Nuz_::Engine* engine = (Nuz_::Engine*)&Nuz::IEngine::GetGameDevice();
	Nuz_::InputDeviceManager* input = (Nuz_::InputDeviceManager*)&(engine->GetInputDeviceManager());
	auto window = ((Nuz_::Engine*)&Nuz::IEngine::GetGameDevice()) -> GetWindow();
	SDL_Event e;
	input->FrameUpdate();
	Camera2D* camera2DNow = nullptr;
	//Camera3D* camera3DNow = nullptr;
	while (m_mainLoop) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				//作为广播消息派发
			case SDL_QUIT:
				sendMessage(Nuz::IEngine::Message::Quit);
				break;

			case SDL_WINDOWEVENT: {
				switch (e.window.event) {
				case SDL_WINDOWEVENT_CLOSE:
					sendMessage(Nuz::IEngine::Message::CloseWindow);
					break;
				case SDL_WINDOWEVENT_MAXIMIZED:
					sendMessage(Nuz::IEngine::Message::WindowMaximized);
					break;
				case SDL_WINDOWEVENT_MINIMIZED:
					sendMessage(Nuz::IEngine::Message::WindowMinimized);
					break;
				case SDL_WINDOWEVENT_RESTORED:
					sendMessage(Nuz::IEngine::Message::WindowRestored);
					break;
				};
				break;
			}
			default:
				//作为输入派发
				input->DispatchEvent(e);
				break;
			};
		}


		//初始化GL状态机
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//准备收集要绘制的物体
		drawTask2D.clear();
		drawTask3D.clear();
		
		

		//场景生命周期，在这里处理场景的生命周期
		now->OnUpdate(drawTask2D,drawTask3D,nullptr,nullptr);

		sort(drawTask2D.begin(), drawTask2D.end());
		sort(drawTask3D.begin(), drawTask3D.end());

		//绘制在计划中的物体
		glMatrixPushEXT(GL_PROJECTION);
		/*glEnable(GL_DEPTH_TEST);
		for (auto& p : drawTask3D) {
			p.camera->UseMe();
			p.gof->OnDraw3D();
		}
		glDisable(GL_DEPTH_TEST);*/

		for (auto& p : drawTask2D) {
			if (camera2DNow != p.camera) {
				camera2DNow = p.camera;
				if (camera2DNow != nullptr)
					camera2DNow->UseMe();
				else
					glMatrixLoadIdentityEXT(GL_PROJECTION);
			}
			p.gof->OnDraw2D();
		}

		glMatrixPopEXT(GL_PROJECTION);
		camera2DNow = nullptr;
		//camera3DNow = nullptr;

		SDL_GL_SwapWindow(window);
		float fps = waitFps(60/engine->GetSkipFrame());

		if (engine->GetFPSShowEnable()) {
			std::string title = 
				((Nuz_::Engine*)&Nuz::IEngine::GetGameDevice())->GetWindowTitle() 
				+ "  FPS:" + 
				std::to_string(fps);
			SDL_SetWindowTitle(window, title.c_str());
			title.clear();
		}
	}
	//跳出主循环后应当停止所有声音
}

