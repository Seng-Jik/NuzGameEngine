#pragma once
#include <memory>
#include <string>
namespace Nuz{
	class IComponent;

	/* ���
	* ��Ϸ��һ�����Թ����������Ʒ��
	*/
	class IGameObject{
	public:
	    virtual ~IGameObject(){};

		/* �������
         * ͬһ�������ι��غ͵��ι���ûʲô��ͬ
		 * @param ���ʵ��
		 */
		virtual void MountComponent(std::shared_ptr<IComponent>) = 0;

		/* ж���ѹ������
		 * @param name �������
		 */
		virtual void UnmountComponent(const std::string& name) = 0;

		/* ��ȡ�ѹ������ʵ��
		 * @param name �������
		 * @result ���ʵ��
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& name) = 0;

		/* �������
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
		virtual std::shared_ptr<IGameObject> GetMountedGameObject(const std::string& name) = 0;

		/* ��ȡ�������
		 * @result �������
		 */
        virtual std::string GetName() = 0;

        /* �������
         * �������ʱ�����Ʊ��뱣֤Ψһ�����򵯳��쳣��
         * @param name �������
         * @result ���ʵ��
         */
        static std::shared_ptr<IGameObject> CreateGameObject(const std::string& name);

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
