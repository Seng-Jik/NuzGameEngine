#pragma once
#include <memory>
#include "../../../include/Nuz/SceneManager/GameObject.h"
#include "../../../include/Nuz/SceneManager/Component.h"
#include "GameObjectFloder.h"

namespace Nuz_ {
	class GameObject:public Nuz::IGameObject {
	private:
		GameObjectFloder m_gof;
		GameObjectFloder* m_parent = nullptr;
	public:
		void UnmountSelf();
		void MountComponent(const std::shared_ptr<Nuz::IComponent>& p, const std::string& mountName = "") override;
		void UnmountComponent(const std::string& mountName) override;
		std::shared_ptr<Nuz::IComponent> GetMountedComponent(const std::string& mountName) const override;
		void MountGameObject(const std::shared_ptr<IGameObject>& p, const std::string& mountName = "") override;
		void UnmountGameObject(const std::string& mountName) override;
		std::shared_ptr<IGameObject> GetMountedGameObject(const std::string& mountName) const override;
		GameObjectFloder& GetGameObjectFloader();
		inline void SetParent(GameObjectFloder* p) {
			m_parent = p;
		}
		inline GameObjectFloder* GetParent() {
			return m_parent;
		}
	};
}