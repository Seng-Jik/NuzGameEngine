#include "SceneManager.h"
#include "Scene.h"
#include "../Engine.h"
#include <set>
#include "DrawTask.h"
#include "GameObjectFloder.h"
#include "Camera2D.h"
#include <SDL_mixer.h>
//#include "Camera3D.h"
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
	m_frameTime = 0;
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
		for (int i = 0; i < engine->GetSkipFrame(); ++i) {
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

			//׼���ռ�Ҫ���Ƶ�����
			drawTask2D.clear();
			drawTask3D.clear();

			//�����л�
			if (m_fadeTask.type != FadeSceneTask::NONE) {
				//�����ǰҪ���л�����
				if (m_fadeTask.type == FadeSceneTask::FADE_MODE_START) {
					if (m_fadeTask.time > 0) {
						now->OnFadeSwitchOut(m_fadeTask.time);
						m_fadeTask.to->OnFadeSwitchIn(m_fadeTask.time);
						m_fadeTask.type = FadeSceneTask::FADE_MODE;
						m_fadeTask.timePassed = 0;
					}
					else if (m_fadeTask.time == 0) {
						now = m_fadeTask.to;
						m_fadeTask.type = FadeSceneTask::NONE;
					}
				}

				//��������л�����
				if (m_fadeTask.type == FadeSceneTask::FADE_MODE) {
					float progress = float(m_fadeTask.timePassed++) / m_fadeTask.time;
					m_fadeTask.to->OnFadeSwitchInUpdate(progress);
					now->OnFadeSwitchOutUpdate(progress);
					if (m_fadeTask.timePassed >= m_fadeTask.time) {
						//����л�����
						now = m_fadeTask.to;
						m_fadeTask.type = FadeSceneTask::NONE;
					}
				}
			}

			//�����������ڣ������ﴦ��������������
			now->OnUpdate(drawTask2D, drawTask3D, nullptr, nullptr);
			if(m_fadeTask.type == FadeSceneTask::FADE_MODE) m_fadeTask.to->OnUpdate(drawTask2D, drawTask3D, nullptr, nullptr);
		}
		m_frameTime += engine->GetSkipFrame();

		//��ʼ��GL״̬��
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sort(drawTask2D.begin(), drawTask2D.end());
		sort(drawTask3D.begin(), drawTask3D.end());

		//�����ڼƻ��е�����
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
	//������ѭ����Ӧ��ֹͣ��������
	Mix_HaltChannel(-1);
}

//Main Loop

void Nuz_::SceneManager::FadeTo(std::shared_ptr<Nuz::IScene> s, int time) {
	if (m_fadeTask.type != FadeSceneTask::NONE) throw runtime_error("Scene manager is busy.");
	m_fadeTask.type = FadeSceneTask::FADE_MODE_START;
	m_fadeTask.to = (Nuz_::Scene*)s.get();
	m_fadeTask.time = time;
}

