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

/* ������������ȡ���ڵ��ж�Ӧ�����������
* @param ������
*/

std::shared_ptr<IComponent> Nuz::IComponent::GetOtherComponent(const std::string & mountName) const
{
	return m_parent->GetMountedComponent(mountName);
}

/* ������������ȡ���ڵ��ж�Ӧ�����������
* @param ������
*/

std::shared_ptr<IGameObject> Nuz::IComponent::GetGameObject(const std::string & mountName) const {
	return m_parent->GetMountedGameObject(mountName);
}

/* �Ӹ��ڵ���ж������
*/

void Nuz::IComponent::UnmountSelf() {
	m_parent->UnmountComponent(this);
}

/* ������������ȡ���ڵ��ж�Ӧ�����������
* @param ������
*/

