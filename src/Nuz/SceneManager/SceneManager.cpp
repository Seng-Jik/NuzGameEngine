#include "SceneManager.h"
#include "Scene.h"
#include "../Engine.h"
#include <set>
#include "DrawTask.h"
#include "GameObjectFloder.h"
#include "Camera2D.h"
#include <SDL.h>
#include "../Renderer/OpenGL/glew.h"

using namespace Nuz_;
using namespace std;

/* ��׼FPS���ƣ�����ֵΪFPSֵ */
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
	static multiset<DrawTask> drawTask;
	Nuz_::Scene* now = (Nuz_::Scene*)p.get();
	Nuz_::Engine* engine = (Nuz_::Engine*)&Nuz::IEngine::GetGameDevice();
	Nuz_::InputDeviceManager* input = (Nuz_::InputDeviceManager*)&(engine->GetInputDeviceManager());
	auto window = ((Nuz_::Engine*)&Nuz::IEngine::GetGameDevice()) -> GetWindow();
	SDL_Event e;
	input->FrameUpdate();
	while (m_mainLoop) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				//��Ϊ�㲥��Ϣ�ɷ�
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
				//��Ϊ�����ɷ�
				input->DispatchEvent(e);
				break;
			};
		}


		//��ʼ��GL״̬��
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//׼���ռ�Ҫ���Ƶ�����
		drawTask.clear();
		
		

		//�����������ڣ������ﴦ��������������
		now->OnUpdate(drawTask,nullptr,nullptr);

		//�����ڼƻ��е�����
		glMatrixPushEXT(GL_PROJECTION);
		for (auto& p : drawTask) {
			//p.camera3D->UseMe();
			//now->OnDraw3D();
			p.camera2D->UseMe();
			p.gof->OnDraw2D();
		}

		glMatrixPopEXT(GL_PROJECTION);

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

