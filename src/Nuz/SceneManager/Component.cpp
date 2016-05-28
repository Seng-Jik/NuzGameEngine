#include "../../../include/Nuz/SceneManager/Component.h"
#include "GameObjectFloder.h"
#include "../../../include/Nuz/SceneManager/Scene.h"
using namespace Nuz;

std::shared_ptr<IScene> Nuz::IComponent::GetParentAsScene() const
{
	return m_parent->GetSCParent();
}

std::shared_ptr<IGameObject> Nuz::IComponent::GetParentAsGameObject() const
{
	return m_parent->GetGOParent();
}

/* 给定挂载名，取父节点中对应挂载名的组件
* @param 挂载名
*/

std::shared_ptr<IComponent> Nuz::IComponent::GetOtherComponent(const std::string & mountName) const
{
	return m_parent->GetMountedComponent(mountName);
}

/* 给定挂载名，取父节点中对应挂载名的物件
* @param 挂载名
*/

std::shared_ptr<IGameObject> Nuz::IComponent::GetGameObject(const std::string & mountName) const {
	return m_parent->GetMountedGameObject(mountName);
}

std::shared_ptr<const ICamera2D> Nuz::IComponent::GetCamera2D() const
{
	if (m_parentType != ParentType::None) {
		return m_parent->GetCamera2D().lock();
	}
	else return std::shared_ptr<ICamera2D>(nullptr);
}

/* 从父节点上卸载自身
*/

void Nuz::IComponent::UnmountSelf() {
	m_parent->UnmountComponent(this);
}

/* 给定挂载名，取父节点中对应挂载名的组件
* @param 挂载名
*/

