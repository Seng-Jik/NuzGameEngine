#pragma once
#include <memory>
#include <string>
#include "Camera2D.h"
#include "Camera3D.h"

namespace Nuz{
	class IComponent;
	class IGameObject;

	/* ����
	 * ��Ϸ��һ�����Թ��������������ӳ����ĳ��档
     * �ϲ㳡�����������²㳡�����Ϸ���
     * �����ᱻת��Ϊ2Dͼ����и�����ʾ��
	 */
	class IScene{
	public:
	    virtual ~IScene(){};

		/* �������
		 * ͬһ�������ι��غ͵��ι���ûʲô��ͬ
		 * @param ���ʵ��
		 * @param mountName ����������������
		 */
		virtual void MountComponent(const std::shared_ptr<IComponent>&,const std::string mountName = "") = 0;

		/* ж���ѹ��ص��ó��������
		 * @param name �������
		 */
		virtual void UnmountComponent(const std::string& name) = 0;

        /* ж���ѹ��ص��ó��������
		 * @param mountName �������
		 */
		virtual void UnmountComponentByMountName(const std::string& mountName) = 0;

		/* ��ȡ�ѹ��ص��ó������ʵ��
		 * @param mountName ������
		 * @result ���ʵ��
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& mountName) const = 0;

		/* �������
		 * ͬһ����������ض�κ͹���һ��ûʲô��ͬ��
		 * @param ���ʵ��
		 * @param mountName ������������������
		 */
		virtual void MountGameObject(const std::shared_ptr<IGameObject>&,const std::string& mountName = "") = 0;

		/* ж���ѹ������
		 * @param name �������
		 */
		virtual void UnmountGameObject(const std::string& name) = 0;

        /* ж���ѹ������
		 * @param mountNameame ���������
		 */
		virtual void UnmountGameObjectByMountName(const std::string& mountName) = 0;

		/* ��ȡ�ѹ������ʵ��
		 * @param mountName ���������
		 * @result ���ʵ��
		 */
		virtual std::shared_ptr<IGameObject> GetMountedGameObject(const std::string& mountName) const = 0;

		/* ����һ������
		 * @param ����ʵ��
		 */
		virtual void MountScene(const std::shared_ptr<IScene>&) = 0;

		/* ж���ѹ��صĳ���
		 * @param name ��������
		 */
		virtual void UnmountScene(const std::string& name);

		/* ���������
		 * 2D/3D��������ɸ�����һ����
		 * @param camera �����
		 */
        virtual void SetCamera2D(const std::shared_ptr<const ICamera2D>& camera) = 0;
        virtual void SetCamera3D(const std::shared_ptr<const ICamera3D>& camera) = 0;

		/* ��ȡ��������
		 * @result ��������
		 */
        virtual std::string GetName() const = 0;

		/* ��������
         * ��������ʱ�����Ʊ��뱣֤Ψһ�����򵯳��쳣��
		 * @param name ��������
         * @result ����ʵ��
         */
        static std::shared_ptr<IScene> CreateScene(const std::string& name);

        /* ͨ�����ƻ�ȡ����
         * @param name ��������
         * @result ����
         */
        static std::shared_ptr<IScene> GetScene(const std::string& name);
	};
}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��28�գ�
 * ���� ��������
 */
