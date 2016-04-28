#pragma once
#include <memory>
#include <string>
namespace Nuz{
	class IComponent;
	class IGameObject;

	/* ����
	* ��Ϸ��һ�����Թ��������������ӳ����ĳ��档
	*/
	class IScene{
	public:
	    virtual ~IScene(){};

		/* �������
		 * ͬһ�������ι��غ͵��ι���ûʲô��ͬ
		 * @param ���ʵ��
		 */
		virtual void MountComponent(std::shared_ptr<IComponent>) = 0;

		/* ж���ѹ��ص��ó��������
		 * @param name �������
		 */
		virtual void UnmountComponent(const std::string& name) = 0;

		/* ��ȡ�ѹ��ص��ó������ʵ��
		 * @param name �������
		 * @result ���ʵ��
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& name) = 0;

		/* �������
		 * ͬһ����������ض�κ͹���һ��ûʲô��ͬ��
		 * @param ���ʵ��
		 */
		virtual void MountGameObject(std::shared_ptr<IGameObject>) = 0;

		/* ж���ѹ������
		 * @param name �������
		 */
		virtual void UnmountGameObject(const std::string& name) = 0;

		/* ��ȡ�ѹ������ʵ��
		 * @param name �������
		 * @result ���ʵ��
		 */
		virtual std::shared_ptr<IComponent> GetMountedGameObject(const std::string& name) = 0;

		/* ����һ������
		 * @param ����ʵ��
		 */
		virtual void MountScene(std::shared_ptr<IScene>) = 0;

		/* ж���ѹ��صĳ���
		 * @param name ��������
		 */
		virtual void UnmountScene(const std::string& name);

		/* ��ȡ�ѹ��صĳ���
		 * @param name ��������
		 * @result ����ʵ��
		 */
		virtual std::shared_ptr<IScene> GetMountedScene(const std::string& name);

		/* ��ȡ��������
		 * @result ��������
		 */
        virtual std::string GetName() = 0;

		/* ��������
         * ��������ʱ�����Ʊ��뱣֤Ψһ�����򵯳��쳣��
		 * @param name ��������
         * @result ����ʵ��
         */
        static std::shared_ptr<IScene> CreateScene(const std::string& name);
	};
}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��28�գ�
 * ���� ��������
 */
