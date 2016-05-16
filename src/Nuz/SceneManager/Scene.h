#pragma once
#include <string>
#include <map>
#include <memory>
#include "../../../include/Nuz/SceneManager/Scene.h"

namespace Nuz_ {
	class Scene :public Nuz::IScene {
	private:
		std::string m_name;

		friend std::shared_ptr<Nuz::IScene> Nuz::IScene::CreateScene(const std::string& name);
		friend std::shared_ptr<Nuz::IScene> Nuz::IScene::GetScene(const std::string& name);
		static std::map<std::string, std::weak_ptr<Nuz::IScene>> m_name2ptr;

	public:
		virtual ~Scene() {};
		void UnmountSelf() override {};
		void MountComponent(const std::shared_ptr<Nuz::IComponent>&, const std::string mountName = "") override {};
		void UnmountComponent(const std::string& name) override {};
		void UnmountComponentByMountName(const std::string& mountName) override{};
		std::shared_ptr<Nuz::IComponent> GetMountedComponent(const std::string& mountName) const override { return nullptr; };
		void MountGameObject(const std::shared_ptr<Nuz::IGameObject>&, const std::string& mountName = "") override {};
		void UnmountGameObject(const std::string& name) override {};
		void UnmountGameObjectByMountName(const std::string& mountName) override {};
		std::shared_ptr<Nuz::IGameObject> GetMountedGameObject(const std::string& mountName) const override { return nullptr; };
		void MountScene(const std::shared_ptr<IScene>&) override {};
		void UnmountScene(const std::string& name) override {};
		void SetCamera2D(const std::shared_ptr<const Nuz::ICamera2D>& camera) override {};
		void SetCamera3D(const std::shared_ptr<const Nuz::ICamera3D>& camera) override {};
		std::string GetName() const override { return m_name; };


		void OnShow() {};	//当物件开始被显示时执行
		void OnHide() {};	//当物件被隐藏时执行
		void OnUpdate() {};	//当组件需要更新逻辑时执行

		void OnDraw3DReady() {};	//当准备绘制3D时执行
		void OnDraw3D() {};	//当组件需要绘制3D时执行
		void OnDraw3DFinished() {};	//当3D绘制完成后

		void OnDraw2DReady() {};	//当准备绘制2D物件时执行
		void OnDraw2D();	//当组件需要绘制2D物件时执行
		void OnDraw2DFinished() {};	//当2D物件绘制完成后

		void OnDrawSceneReady() {};    //当场景绘制准备开始时
		void OnDrawScene() {}; //当绘制场景时
		void OnDrawSceneFinished() {}; //当场景绘制结束时
		void OnFadeSwitchOut(int timeLimited) {};

		/* 当场景被切出时会增加的增补逻辑
		* @param finished 时间剩余百分比
		*/
		void OnFadeSwitchOutUpdate(float finished) {};

		/* 当场景要求被切入时执行
		* @param timeLimited 时间限制（帧）
		*/
		void OnFadeSwitchIn(int timeLimited) {};

		/* 当场景被切入时会增加的增补逻辑
		* @param finished 时间剩余百分比
		*/
		void OnFadeSwitchInUpdate(float finished) {};
	};
}