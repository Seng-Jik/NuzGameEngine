#pragma once
#include <string>
#include <map>
#include <set>
#include "DrawTask.h"
#include <queue>
#include <memory>
#include "../../../include/Nuz/SceneManager/Scene.h"
#include "GameObjectFloder.h"
namespace Nuz_ {
	class Scene final :public Nuz::IScene {
	private:
		GameObjectFloder m_gof;
		std::map<std::string, std::shared_ptr<Nuz::IScene> > m_name2scene;
		std::set< std::shared_ptr<Nuz::IScene> > m_allscene;
		Scene* m_parent = nullptr;

		std::queue<Nuz::IScene*> m_unmountSceneTask;
		void unmountScene_Really(Nuz::IScene*);

		std::shared_ptr<const Nuz::ICamera2D> m_camera2D;

	public:
		void UnmountSelf() override;

		void MountComponent(const std::shared_ptr<Nuz::IComponent>& p, const std::string mountName = "") override;
		void UnmountComponent(const std::string& mountName) override;
		std::shared_ptr<Nuz::IComponent> GetMountedComponent(const std::string& mountName) const override;
		void MountGameObject(const std::shared_ptr<Nuz::IGameObject>& p, const std::string& mountName = "") override;
		void UnmountGameObject(const std::string& mountName) override;
		std::shared_ptr<Nuz::IGameObject> GetMountedGameObject(const std::string& mountName) const override;

		void MountScene(const std::shared_ptr<IScene>&,const std::string& mountName = "") override;
		void UnmountScene(const std::string& mountName) override;
		inline void UnmountScene(Nuz_::Scene* const p){
			m_unmountSceneTask.push(p);
		}

		inline GameObjectFloder& GetGameObjectFloder() { return m_gof; }

		inline void SetCamera2D(const std::shared_ptr<const Nuz::ICamera2D>& camera) override {
			m_camera2D = camera;
		}
		void SetCamera3D(const std::shared_ptr<const Nuz::ICamera3D>& camera) override {};


		void OnUpdate(std::multiset<DrawTask2D>& drawTask2D, std::multiset<DrawTask3D>& drawTask3D, Camera2D* c2d, Camera3D* c3d);
		//void OnDraw3D();
		//void OnDraw2D();
		void OnFadeSwitchOut(int timeLimited);
		void OnFadeSwitchOutUpdate(float finished);
		void OnFadeSwitchIn(int timeLimited);
		void OnFadeSwitchInUpdate(float finished);
	};
}