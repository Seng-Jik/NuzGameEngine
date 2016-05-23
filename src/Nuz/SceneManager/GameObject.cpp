#include "GameObject.h"
using namespace Nuz;
using namespace Nuz_;

void Nuz_::GameObject::UnmountSelf()
{
	if (m_parent) m_parent->UnmountGameObject(this);
}

void Nuz_::GameObject::MountComponent(const std::shared_ptr<Nuz::IComponent>& p, const std::string & mountName) {
	m_gof.MountComponent(p, mountName);
}

void Nuz_::GameObject::UnmountComponent(const std::string & mountName) {
	m_gof.UnmountComponent(mountName);
}

std::shared_ptr<Nuz::IComponent> Nuz_::GameObject::GetMountedComponent(const std::string & mountName) const {
	return m_gof.GetMountedComponent(mountName);
}

void Nuz_::GameObject::MountGameObject(const std::shared_ptr<IGameObject>& p, const std::string & mountName) {
	m_gof.MountGameObject(p, mountName);
}

void Nuz_::GameObject::UnmountGameObject(const std::string & mountName) {
	m_gof.UnmountGameObject(mountName);
}

std::shared_ptr<IGameObject> Nuz_::GameObject::GetMountedGameObject(const std::string & mountName) const {
	return m_gof.GetMountedGameObject(mountName);
}

GameObjectFloder & Nuz_::GameObject::GetGameObjectFloader() { return m_gof; }

std::shared_ptr<IGameObject> Nuz::IGameObject::CreateGameObject()
{
	auto p= std::shared_ptr<GameObject>(new GameObject);
	p->GetGameObjectFloader().SetParent(p);
	return p;
}
