#include "SceneManager.h"
#include "Scene.h"
#include "../Engine.h"
#include <SDL.h>
#include "../Renderer/OpenGL/glew.h"

using namespace Nuz_;

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
	Nuz_::Scene* now = (Nuz_::Scene*)p.get();
	Nuz_::Engine* engine = (Nuz_::Engine*)&Nuz::IEngine::GetGameDevice();
	auto window = ((Nuz_::Engine*)&Nuz::IEngine::GetGameDevice()) -> GetWindow();
	SDL_Event e;
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
				break;
			};
		}


		//初始化GL状态机
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//场景生命周期，在这里处理场景的生命周期
		now->OnUpdate();
		now->OnDrawScreenReady();
		now->OnDraw3D();
		now->OnDraw2D();
		now->OnDrawScreenFinished();

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
}

