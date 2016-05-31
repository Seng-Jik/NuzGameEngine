#pragma once
#include <map>
#include <memory>
#include <vector>
#include <set>
#include <queue>
#include "../../../include/Nuz/SceneManager/Component.h"

namespace Nuz_ {
	struct DrawTask2D;
	struct DrawTask3D;
	class Camera2D;
	class Camera3D;
	class GameObjectFloder final {
	public:
		enum ParentType { SCENE, GAMEOBJECT };
	private:
		int m_drawLevel = 0;

		std::map<std::string, std::shared_ptr<Nuz::IComponent>> m_mountName2component;
		std::vector<std::shared_ptr<Nuz::IComponent>> m_allcomponent;

		std::map<std::string, std::shared_ptr<Nuz::IGameObject>> m_mountName2go;
		std::vector<std::shared_ptr<Nuz::IGameObject>> m_allgo;

		ParentType m_parentType;
		std::weak_ptr<Nuz::IGameObject> m_goParent;
		std::weak_ptr<Nuz::IScene> m_scParent;
		std::weak_ptr<const Nuz::ICamera2D> m_camera2D;

		std::queue<Nuz::IComponent*> m_unmountCompoTask;
		std::queue<Nuz::IGameObject*> m_unmountGOTask;
		void unmountGameObject_Really(Nuz::IGameObject*);
		void unmountComponent_Really(Nuz::IComponent*);
	public:
		void SetParent(const std::shared_ptr<Nuz::IGameObject>& p);
		void SetParent(const std::shared_ptr<Nuz::IScene>& p);

		inline void SetCamera2D(const std::shared_ptr<const Nuz::ICamera2D>& p) {
			m_camera2D = p;
		}

		inline std::weak_ptr<const Nuz::ICamera2D> GetCamera2D() {
			return m_camera2D;
		}

		inline ParentType GetParentType() { return m_parentType; }
		inline std::shared_ptr<Nuz::IGameObject> GetGOParent() { return m_goParent.lock(); }
		inline std::shared_ptr<Nuz::IScene> GetSCParent() { return m_scParent.lock(); }

		void MountComponent(const std::shared_ptr<Nuz::IComponent>&, const std::string& mountName = "");
		inline void UnmountComponent(const std::string& mountName)
		{
			if (m_mountName2component.count(mountName) == 1) {
				m_unmountCompoTask.push(m_mountName2component.at(mountName).get());
			}
		}
		inline void UnmountComponent(Nuz::IComponent* p) {
			m_unmountCompoTask.push(p);
		}
		inline std::shared_ptr<Nuz::IComponent> GetMountedComponent(const std::string& mountName) const
		{
			if (m_mountName2component.count(mountName) == 0) return std::shared_ptr<Nuz::IComponent>(nullptr);
			else return m_mountName2component.at(mountName);
		}

		void MountGameObject(const std::shared_ptr<Nuz::IGameObject>&, const std::string& mountName = "");
		inline void UnmountGameObject(const std::string& mountName)
		{
			if (m_mountName2go.count(mountName) == 1) {
				m_unmountGOTask.push(m_mountName2go.at(mountName).get());
			}
		}
		inline void UnmountGameObject(Nuz::IGameObject* p) {
			m_unmountGOTask.push(p);
		}
		std::shared_ptr<Nuz::IGameObject> GetMountedGameObject(const std::string& mountName) const;

		inline void SetDrawLevel(int i) { m_drawLevel = i; }
		inline int GetDrawLevel() { return m_drawLevel; }

		void OnUpdate(std::vector<DrawTask2D>& drawTask2D, std::vector<DrawTask3D>& drawTask3D, Camera2D* c2d, Camera3D* c3d);
		void OnDraw3D();
		void OnDraw2D();
		//void OnDrawScreenReady();
		//void OnDrawScreenFinished();
		void OnFadeSwitchOut(int timeLimited);
		void OnFadeSwitchOutUpdate(float finished);
		void OnFadeSwitchIn(int timeLimited);
		void OnFadeSwitchInUpdate(float finished);
	};
}