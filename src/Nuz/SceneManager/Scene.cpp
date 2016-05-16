#include "Scene.h"
#include <stdexcept>
#include <SDL_opengl.h>
using namespace std;
std::map<std::string, std::weak_ptr<Nuz::IScene>> Nuz_::Scene::m_name2ptr;
std::shared_ptr<Nuz::IScene> Nuz::IScene::CreateScene(const std::string& name) {
	if (Nuz_::Scene::m_name2ptr.count(name)) throw runtime_error("Can not create scene " + name + ",it already existed.");
	auto pScene = std::shared_ptr<Nuz::IScene>(new Nuz_::Scene);
	if(!name.empty()) Nuz_::Scene::m_name2ptr[name] = weak_ptr<Nuz::IScene>(pScene);
	return pScene;
}

std::shared_ptr<Nuz::IScene> Nuz::IScene::GetScene(const std::string& name) {
	if (Nuz_::Scene::m_name2ptr.count(name)) {
		auto& p = Nuz_::Scene::m_name2ptr.at(name);
		if (!p.expired()) {
			return p.lock();
		}
		else {
			Nuz_::Scene::m_name2ptr.erase(name);
		}
	}
	throw Nuz::IScene::SceneNotFound("Scene " + name + "not found.");
}

void Nuz_::Scene::OnDraw2D() {
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}