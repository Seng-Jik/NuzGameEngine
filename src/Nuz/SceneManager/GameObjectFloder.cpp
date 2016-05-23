#include "GameObjectFloder.h"
#include "GameObject.h"

void Nuz_::GameObjectFloder::MountComponent(const std::shared_ptr<Nuz::IComponent>& p, const std::string& mountName)
{
	if (m_allcomponent.count(p) == 0) {
		m_allcomponent.insert(p);
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
}

void Nuz_::GameObjectFloder::unmountComponent_Really(Nuz::IComponent* pIn)
{
	for (auto& p : m_allcomponent) {
		if (p.get() == pIn) {
			p->m_parentType = Nuz::IComponent::ParentType::None;
			p->m_parent = nullptr;
			m_allcomponent.erase(p);
			break;
		}
	}
	for (auto& p : m_mountName2component) {
		if (p.second.get() == pIn) {
			m_mountName2component.erase(p.first);
			break;
		}
	}
}

void Nuz_::GameObjectFloder::unmountGameObject_Really(Nuz::IGameObject* pIn)
{
	for (auto& p : m_allgo) {
		if (p.get() == pIn) {
			((GameObject*)pIn)->SetParent(nullptr);
			m_allgo.erase(p);
			break;
		}
	}
	for (auto& p : m_mountName2go) {
		if (p.second.get() == pIn) {
			m_mountName2go.erase(p.first);
			break;
		}
	}
}

void Nuz_::GameObjectFloder::MountGameObject(const std::shared_ptr<Nuz::IGameObject>& p, const std::string & mountName)
{
	if (m_allgo.count(p) == 0) {
		m_allgo.insert(p);
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
}

std::shared_ptr<Nuz::IGameObject> Nuz_::GameObjectFloder::GetMountedGameObject(const std::string & mountName) const
{
	if (m_mountName2go.count(mountName) == 0) return std::shared_ptr<Nuz::IGameObject>(nullptr);
	else return m_mountName2go.at(mountName);
}

void Nuz_::GameObjectFloder::OnUpdate()
{
	while (!m_unmountCompoTask.empty()) {
		unmountComponent_Really(m_unmountCompoTask.front());
		m_unmountCompoTask.pop();
	}
	while (!m_unmountCompoTask.empty()) {
		unmountGameObject_Really(m_unmountGOTask.front());
		m_unmountCompoTask.pop();
	}
	for (auto& p : m_allcomponent)
		p->OnUpdate();
	for (auto& p : m_allgo) 
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnUpdate();
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

void Nuz_::GameObjectFloder::OnDrawScreenReady()
{
	for (auto& p : m_allcomponent)
		p->OnDrawScreenReady();
	for (auto& p : m_allgo) {
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnDrawScreenReady();
	}
}

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


void Nuz_::GameObjectFloder::OnDrawScreenFinished()
{
	for (auto& p : m_allcomponent)
		p->OnDrawScreenFinished();
	for (auto& p : m_allgo) {
		(((Nuz_::GameObject*)p.get())->GetGameObjectFloader()).OnDrawScreenFinished();
	}
}
