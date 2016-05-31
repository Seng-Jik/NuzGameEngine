#include "GameObjectFloder.h"
#include "GameObject.h"
#include "DrawTask.h"
#include "Scene.h"

void Nuz_::GameObjectFloder::MountComponent(const std::shared_ptr<Nuz::IComponent>& p, const std::string& mountName)
{
	m_allcomponent.push_back(p);
	if (m_parentType == GAMEOBJECT) {
		p->m_parentType = Nuz::IComponent::ParentType::TypeGameObject;
	}
	else if (m_parentType == SCENE) {
		p->m_parentType = Nuz::IComponent::ParentType::TypeScene;
	}
	p->m_parent = this;
	if (!mountName.empty()) {
		if(m_mountName2component.count(mountName) == 1)
			throw std::runtime_error("Component mount name has already exist.");
		else m_mountName2component[mountName] = p;
	}
}

void Nuz_::GameObjectFloder::unmountComponent_Really(Nuz::IComponent* pIn)
{
	auto ers = find_if(m_allcomponent.begin(), m_allcomponent.end(), [pIn](const std::shared_ptr<Nuz::IComponent>& p) {
		if (p.get() == pIn) {
			p->m_parentType = Nuz::IComponent::ParentType::None;
			p->m_parent = nullptr;
			return true;
		}
		return false;
	});
	m_allcomponent.erase(ers);

	for (auto& p : m_mountName2component) {
		if (p.second.get() == pIn) {
			m_mountName2component.erase(p.first);
			break;
		}
	}
}

void Nuz_::GameObjectFloder::SetParent(const std::shared_ptr<Nuz::IScene>& p) {
	m_scParent = p;
	m_parentType = ParentType::SCENE;
	m_camera2D = ((Nuz_::Scene*)p.get())->GetCamera2D();
}

void Nuz_::GameObjectFloder::SetParent(const std::shared_ptr<Nuz::IGameObject>& p) {
	m_goParent = p;
	m_parentType = ParentType::GAMEOBJECT;
	m_camera2D = ((Nuz_::GameObject*)(p.get()))->GetGameObjectFloader().GetCamera2D();
}

void Nuz_::GameObjectFloder::unmountGameObject_Really(Nuz::IGameObject* pIn)
{
	auto ers = find_if(m_allgo.begin(), m_allgo.end(), [pIn](const std::shared_ptr<Nuz::IGameObject>& p) {
		if (p.get() == pIn) {
			((GameObject*)pIn)->SetParent(nullptr);
			return true;
		}
		return false;
	});
	for (auto& p : m_mountName2go) {
		if (p.second.get() == pIn) {
			m_mountName2go.erase(p.first);
			break;
		}
	}
}

void Nuz_::GameObjectFloder::MountGameObject(const std::shared_ptr<Nuz::IGameObject>& p, const std::string & mountName)
{
	m_allgo.push_back(p);
	if (!mountName.empty()) {
		if (m_mountName2go.count(mountName) == 1) 
			throw std::runtime_error("Game Object mount name has already exist.");
		else {
			if(((GameObject*)p.get())->GetParent()!=nullptr) throw std::runtime_error("Game object has mounted by other.");
			m_mountName2go[mountName] = p;
			((GameObject*)p.get())->SetParent(this);
		}
	}
}

std::shared_ptr<Nuz::IGameObject> Nuz_::GameObjectFloder::GetMountedGameObject(const std::string & mountName) const
{
	if (m_mountName2go.count(mountName) == 0) return std::shared_ptr<Nuz::IGameObject>(nullptr);
	else return m_mountName2go.at(mountName);
}

void Nuz_::GameObjectFloder::OnUpdate(std::vector<DrawTask2D>& drawTask2D, std::vector<DrawTask3D>& drawTask3D, Camera2D* c2d, Camera3D* c3d)
{
	bool needDraw2D = false,needDraw3D = false;
	while (!m_unmountCompoTask.empty()) {
		unmountComponent_Really(m_unmountCompoTask.front());
		m_unmountCompoTask.pop();
	}
	while (!m_unmountCompoTask.empty()) {
		unmountGameObject_Really(m_unmountGOTask.front());
		m_unmountCompoTask.pop();
	}
	for (auto& p : m_allcomponent) {
		bool draw2d = false, draw3d = false;
		p->OnUpdate(draw2d, draw3d);
		needDraw2D = draw2d || needDraw2D;
		needDraw3D = draw3d || needDraw3D;
	}

	static DrawTask2D dt2d;
	if (needDraw2D) {
		dt2d.camera = c2d;
		dt2d.gof = this;
		drawTask2D.push_back(dt2d);
	}

	static DrawTask3D dt3d;
	if (needDraw3D) {
		dt3d.camera = c3d;
		dt3d.gof = this;
		drawTask3D.push_back(dt3d);
	}

	for (auto& p : m_allgo)
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnUpdate(drawTask2D,drawTask3D, c2d, c3d);
}

void Nuz_::GameObjectFloder::OnDraw3D()
{
	for (auto& p : m_allcomponent) {
		p->OnDraw3DReady();
	}
	for (auto& p : m_allcomponent) {
		p->OnDraw3D();
	}
	for (auto& p : m_allcomponent) {
		p->OnDraw3DFinished();
	}
	for (auto& p : m_allgo) 
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnDraw3D();
}

void Nuz_::GameObjectFloder::OnDraw2D()
{
	for (auto& p : m_allcomponent) {
		p->OnDraw2DReady();
	}
	for (auto& p : m_allcomponent) {
		p->OnDraw2D();
	}
	for (auto& p : m_allcomponent) {
		p->OnDraw2DFinished();
	}
	for (auto& p : m_allgo) {
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnDraw2D();
	}
}
/*
void Nuz_::GameObjectFloder::OnDrawScreenReady()
{
	for (auto& p : m_allcomponent)
		p->OnDrawScreenReady();
	for (auto& p : m_allgo) {
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnDrawScreenReady();
	}
}*/

void Nuz_::GameObjectFloder::OnFadeSwitchOutUpdate(float finished)
{
	for (auto& p : m_allcomponent) {
		p->OnFadeSwitchOutUpdate(finished);
	}
	for (auto& p : m_allgo) {
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnFadeSwitchOutUpdate(finished);
	}
}

void Nuz_::GameObjectFloder::OnFadeSwitchIn(int timeLimited)
{
	for (auto& p : m_allcomponent) {
		p->OnFadeSwitchIn(timeLimited);
	}
	for (auto& p : m_allgo) {
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnFadeSwitchIn(timeLimited);
	}
}

void Nuz_::GameObjectFloder::OnFadeSwitchInUpdate(float finished)
{
	for (auto& p : m_allcomponent) {
		p->OnFadeSwitchInUpdate(finished);
	}
	for (auto& p : m_allgo) {
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnFadeSwitchInUpdate(finished);
	}
}

void Nuz_::GameObjectFloder::OnFadeSwitchOut(int timeLimited)
{
	for (auto& p : m_allcomponent) {
		p->OnFadeSwitchOut(timeLimited);
	}
	for (auto& p : m_allgo) {
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnFadeSwitchOut(timeLimited);
	}
}

/*
void Nuz_::GameObjectFloder::OnDrawScreenFinished()
{
	for (auto& p : m_allcomponent)
		p->OnDrawScreenFinished();
	for (auto& p : m_allgo) {
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnDrawScreenFinished();
	}
}*/
