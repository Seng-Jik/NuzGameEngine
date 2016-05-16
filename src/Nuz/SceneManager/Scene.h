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


		void OnShow() {};	//�������ʼ����ʾʱִ��
		void OnHide() {};	//�����������ʱִ��
		void OnUpdate() {};	//�������Ҫ�����߼�ʱִ��

		void OnDraw3DReady() {};	//��׼������3Dʱִ��
		void OnDraw3D() {};	//�������Ҫ����3Dʱִ��
		void OnDraw3DFinished() {};	//��3D������ɺ�

		void OnDraw2DReady() {};	//��׼������2D���ʱִ��
		void OnDraw2D();	//�������Ҫ����2D���ʱִ��
		void OnDraw2DFinished() {};	//��2D���������ɺ�

		void OnDrawSceneReady() {};    //����������׼����ʼʱ
		void OnDrawScene() {}; //�����Ƴ���ʱ
		void OnDrawSceneFinished() {}; //���������ƽ���ʱ
		void OnFadeSwitchOut(int timeLimited) {};

		/* ���������г�ʱ�����ӵ������߼�
		* @param finished ʱ��ʣ��ٷֱ�
		*/
		void OnFadeSwitchOutUpdate(float finished) {};

		/* ������Ҫ������ʱִ��
		* @param timeLimited ʱ�����ƣ�֡��
		*/
		void OnFadeSwitchIn(int timeLimited) {};

		/* ������������ʱ�����ӵ������߼�
		* @param finished ʱ��ʣ��ٷֱ�
		*/
		void OnFadeSwitchInUpdate(float finished) {};
	};
}