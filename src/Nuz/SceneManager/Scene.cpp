#include "Scene.h"
#include <stdexcept>
#include "../Renderer/OpenGL/glew.h"
#include "Camera2D.h"
using namespace std;

std::shared_ptr<Nuz::IScene> Nuz::IScene::CreateScene() {
	auto p = std::shared_ptr<Nuz_::Scene>(new Nuz_::Scene);
	p->GetGameObjectFloder().SetParent(p);
	return p;
}

void Nuz_::Scene::unmountScene_Really(Nuz::IScene * pD)
{
	for (auto& p : m_name2scene) {
		if (p.second.get() == pD) {
			m_name2scene.erase(p.first);
			break;
		}
	}
	for (auto& p : m_allscene) {
		if (p.get() == pD) {
			m_allscene.erase(p);
			((Scene*)pD)->m_parent = nullptr;
			break;
		}
	}
}

void Nuz_::Scene::UnmountSelf()
{
	if (m_parent) m_parent->UnmountScene(this);
}

void Nuz_::Scene::MountComponent(const std::shared_ptr<Nuz::IComponent>& p, const std::string mountName) {
	m_gof.MountComponent(p, mountName);
}

void Nuz_::Scene::UnmountComponent(const std::string & mountName) {
	m_gof.UnmountComponent(mountName);
}

std::shared_ptr<Nuz::IComponent> Nuz_::Scene::GetMountedComponent(const std::string & mountName) const {
	return m_gof.GetMountedComponent(mountName);
}

void Nuz_::Scene::MountGameObject(const std::shared_ptr<Nuz::IGameObject>& p, const std::string & mountName) {
	m_gof.MountGameObject(p, mountName);
}

void Nuz_::Scene::UnmountGameObject(const std::string & mountName) {
	m_gof.UnmountGameObject(mountName);
}

std::shared_ptr<Nuz::IGameObject> Nuz_::Scene::GetMountedGameObject(const std::string & mountName) const {
	return m_gof.GetMountedGameObject(mountName);
}

void Nuz_::Scene::MountScene(const std::shared_ptr<IScene>& p, const std::string & mountName)
{
	((Scene*)p.get())->m_parent = this;
	m_allscene.insert(p);
	if (!mountName.empty()) {
		if (m_name2scene.count(mountName) == 0) {
			m_name2scene[mountName] = p;
		}
		else throw std::runtime_error("This scene mount name has already exist.");
	}
}

void Nuz_::Scene::UnmountScene(const std::string & name)
{
	if (m_name2scene.count(name) == 1) {
		m_unmountSceneTask.push(m_name2scene.at(name).get());
	}
}

void Nuz_::Scene::OnUpdate() {
	while (!m_unmountSceneTask.empty()) {
		unmountScene_Really(m_unmountSceneTask.front());
		m_unmountSceneTask.pop();
	}
	for (auto& p : m_allscene)
		((Scene*)p.get())->OnUpdate();
	m_gof.OnUpdate();
}

void Nuz_::Scene::OnDraw3D() {
	m_gof.OnDraw3D();
	for (auto& p : m_allscene)
		((Scene*)p.get())->OnDraw3D();
}

void Nuz_::Scene::OnDraw2D() {
	if (m_camera2D != nullptr) {
		glMatrixPushEXT(GL_PROJECTION);
		((Camera2D*)m_camera2D.get())->UseMe();
	}
	m_gof.OnDraw2D();
	for (auto& p : m_allscene)
		((Scene*)p.get())->OnDraw2D();
	if (m_camera2D != nullptr) {
		glMatrixPopEXT(GL_PROJECTION);
	}
}

void Nuz_::Scene::OnDrawScreenReady() {
	m_gof.OnDrawScreenReady(); 
	for (auto& p : m_allscene)
		((Scene*)p.get())->OnDrawScreenReady();
}

void Nuz_::Scene::OnDrawScreenFinished() {
	m_gof.OnDrawScreenFinished();
	for (auto& p : m_allscene)
		((Scene*)p.get())->OnDrawScreenFinished();
}

void Nuz_::Scene::OnFadeSwitchOut(int timeLimited) {
	m_gof.OnFadeSwitchOut(timeLimited); 
	for (auto& p : m_allscene)
		((Scene*)p.get())->OnFadeSwitchOut(timeLimited);
}

inline void Nuz_::Scene::OnFadeSwitchOutUpdate(float finished) { 
	m_gof.OnFadeSwitchOutUpdate(finished); 
	for (auto& p : m_allscene)
		((Scene*)p.get())->OnFadeSwitchOutUpdate(finished);
}

void Nuz_::Scene::OnFadeSwitchIn(int timeLimited) {
	m_gof.OnFadeSwitchIn(timeLimited);
	for (auto& p : m_allscene)
		((Scene*)p.get())->OnFadeSwitchIn(timeLimited);
}

void Nuz_::Scene::OnFadeSwitchInUpdate(float finished) { 
	m_gof.OnFadeSwitchInUpdate(finished); 
	for (auto& p : m_allscene)
		((Scene*)p.get())->OnFadeSwitchInUpdate(finished);
}
