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
		/* �������
		 * @param id ���id
		 * @param ���ʵ��
		 */
		virtual void MountComponent(const std::string& id,std::shared_ptr<IComponent>) = 0;

		/* ж���ѹ������
		 * @param id ���id
		 */
		virtual void UnmountComponent(const std::string& id) = 0;

		/* ��ȡ�ѹ������ʵ��
		 * @param id ���id
		 * @result ���ʵ��
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& id) = 0;

		/* �������
		 * @param id ���id
		 * @param ���ʵ��
		 */
		virtual void MountGameObject(const std::string& id,std::shared_ptr<IGameObject>) = 0;

		/* ж���ѹ������
		 * @param id ���id
		 */
		virtual void UnmountGameObject(const std::string& id);

		/* ��ȡ�ѹ������ʵ��
		 * @param id ���id
		 * @result ���ʵ��
		 */
		virtual std::shared_ptr<IComponent> GetMountedGameObject(const std::string& id) = 0;

		/* ����һ������
		 * @param id ����id
		 * @param ����ʵ��
		 */
		virtual void MountScene(const std::string& id,std::shared_ptr<IScene>) = 0;

		/* ж���ѹ��صĳ���
		 * @param id ����id
		 */
		virtual void UnmountScene(const std::string& id);

		/* ��ȡ�ѹ��صĳ���
		 * @param id ����id
		 * @result ����ʵ��
		 */
		virtual std::shared_ptr<IScene> GetMountedScene(const std::string& id);
	};
	/* ��������
	 * @result ����ʵ��
	 */
	std::shared_ptr<IScene> CreateScene();
}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 *
 */
