#pragma once
#include <memory>
#include <string>
namespace Nuz{
	class IComponent;

	/* ���
	 * ��Ϸ��һ�����Թ����������Ʒ��
	 * �²�������������ϲ�������Ϸ���2D���Ƶ�״̬�£���
	 */
	class IGameObject{
	public:
	    virtual ~IGameObject(){};

		/* �������
         * ͬһ�������ι��غ͵��ι���ûʲô��ͬ
         * �������ڱ��������Ψһ�ģ���ȫ�ֿ��������������������Ϊ��λ���������
		 * @param ���ʵ��
		 * @param ���������������������㽫�޷�ͨ���������һ�����
		 */
		virtual void MountComponent(const std::shared_ptr<IComponent>&,const std::string& mountName = "") = 0;

		/* ж���ѹ������
		 * @param name �������
		 */
		virtual void UnmountComponent(const std::string& name) = 0;

		/* ж���ѹ������
		 * @param mountName ���������
		 */
		virtual void UnmountComponentByMountName(const std::string& mountName) = 0;

		/* ��ȡ�ѹ������ʵ��
		 * @param mountName ���������
		 * @result ���ʵ��
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponentByMountName(const std::string& mountName) const = 0;

		/* �������
		 * @param ���ʵ��
		 * @param mountName ���������������������
		 */
		virtual void MountGameObject(const std::shared_ptr<IGameObject>&,const std::string& mountName = "") = 0;

		/* ж���ѹ������
		 * @param name �������
		 */
		virtual void UnmountGameObject(const std::string& name) = 0;

        /* ж���ѹ������
		 * @param name �������
		 */
		virtual void UnmountGameObjectByMountName(const std::string& mountName) = 0;

		/* ��ȡ�ѹ������ʵ��
		 * @param name ���������
		 * @result ���ʵ��
		 */
		virtual std::shared_ptr<IGameObject> GetMountedGameObject(const std::string& mountName) const = 0;

		/* ��ȡ�������
		 * @result �������
		 */
        virtual std::string GetName() const = 0;

        /* �������
         * �������ʱ�����Ʊ��뱣֤Ψһ�����򵯳��쳣��
         * ���Դ����������������������������ƻ�ȡ��
         * @param name �������
         * @result ���ʵ��
         */
        static std::shared_ptr<IGameObject> CreateGameObject(const std::string& name = "");

        /* �������ƻ�ȡ���
         * @param name �������
         * @result ���
         */
        static std::shared_ptr<IGameObject> GetGameObject(const std::string& name);
	};
}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��28�գ�
 * ���� ��������
 */
