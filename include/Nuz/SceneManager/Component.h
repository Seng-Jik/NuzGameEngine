#pragma once
#include <memory>

namespace Nuz{
	class IScene;
	class IGameObject;

	/* ���
	* ����������򳡾��ϵ�һ���߼��͹��ܡ�
	*/
	class IComponent{
	protected:
	public:
	    /* ����ʱע������
	     * ����뱣֤ÿ���������һ��Ψһ���������
	     * �����Ƴ�ͻʱ���ᵯ���쳣
	     * @param name �������
	     */
	    IComponent(const std::string& name);
	    virtual ~IComponent(){};

		virtual void OnInit(){};	//����ʼ����������濪ʼʹ��ʱ
		virtual void OnQuit(){};	//����������ٱ�����ʹ��ʱ
		virtual void OnShow(){};	//�������ʼ����ʾʱִ��
		virtual void OnHide(){};	//�����������ʱִ��
		virtual void OnUpdate(){};	//�������Ҫ�����߼�ʱִ��

		virtual void OnDraw2DReady(){};	//��׼������2Dʱִ��
		virtual void OnDraw2D(){};	//�������Ҫ����2Dʱִ��
		virtual void OnDraw2DFinished(){};	//��2D������ɺ�

		virtual void OnDraw3DReady(){};	//��׼������3Dʱִ��
		virtual void OnDraw3D(){};	//�������Ҫ����3Dʱִ��
		virtual void OnDraw3DFinished(){};	//��3D������ɺ�

		/* ������Ҫ���г�ʱִ��
		 * @param ʱ�����ƣ�֡��
		 */
		virtual void OnFadeSwitchOut(int timeLimited){};

		/* ���������г�ʱ�����ӵ������߼�
		 * @param ʱ��ʣ��ٷֱ�
		 */
		virtual void OnFadeSwitchOutUpdate(float finished){};

		/* ������Ҫ������ʱִ��
		 * @param ʱ�����ƣ�֡��
		 */
		virtual void OnFadeSwitchIn(int timeLimited){};

		/* ������������ʱ�����ӵ������߼�
		 * @param ʱ��ʣ��ٷֱ�
		 */
		virtual void OnFadeSwitchInUpdate(float finished){};

		/* ȡ���������
		 * @result �����
		 */
        virtual std::string GetName() = 0;

        /* �������Ʒ������
         * @param name �����
         * @result ���
         */
        static std::shared_ptr<IComponent> GetComponent(const std::string name);

        /* ���ڵ����� */
		enum class ParentType{
		    None,   //û�б�����
			TypeScene,	//����
			TypeGameObject	//��Ϸ���
		};

		/* ��ȡ���ڵ�����
		 * @result ���ڵ�����
		 */
		virtual ParentType GetParentType() = 0;

		/* ��ȡ��Ϊ����ĸ��ڵ�
		 * @result ���ڵ�ʵ��
		 */
		virtual std::shared_ptr<IGameObject> GetParentGameObject() = 0;

		/* ��ȡ��Ϊ�����ĸ��ڵ�
		 * @result ���ڵ�ʵ��
		 */
		virtual std::shared_ptr<IScene> GetParentScene() = 0;
	};

}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��28�գ�
 * ���� �����������
 */
