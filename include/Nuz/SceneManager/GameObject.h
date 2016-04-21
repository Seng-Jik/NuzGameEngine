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
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& id) = 0;
	};
	/* �������
	 * @result ���ʵ��
	 */
	shared_ptr<IGameObject> CreateGameObject() = 0;
}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 *
 */
