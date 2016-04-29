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

        /* ��ȡ��Ϊ�����ĸ��ڵ�ʵ��
		 * @result ���ڵ�
		 */
		virtual std::shared_ptr<IScene> GetSceneParent() = 0;

        /* ��ȡ��Ϊ����ĸ��ڵ�ʵ��
		 * @result ���ڵ�
		 */
		virtual std::shared_ptr<IGameObject> GetGameObjectParent() = 0;

		/* ������������ȡ���ڵ��ж�Ӧ�����������
		 * @param ������
		 */
        virtual std::shared_ptr<IComponent> GetOtherComponent(const std::string& mountName) = 0;

        /* ������������ȡ���ڵ��ж�Ӧ�����������
		 * @param ������
		 */
        virtual std::shared_ptr<IGameObject> GetGameObjectByMountName(const std::string& mountName) = 0;

        /* ��ȡ��������ڵĳ���
         * @result ��������
         */
        virtual std::string GetSceneName() = 0;
	public:
	    /* ����ʱע������
	     * ����뱣֤ÿ���������һ��Ψһ���������
         * ������Ϊ��ʱ��Ϊ����������������������ƻ�ȡ��
	     * �����Ƴ�ͻʱ���ᵯ���쳣
	     * @param name �������
	     */
	    IComponent(const std::string& name = "");
	    virtual ~IComponent(){};

		virtual void OnInit(){};	//����ʼ����������濪ʼʹ��ʱ
		virtual void OnQuit(){};	//����������ٱ�����ʹ��ʱ
		virtual void OnShow(){};	//�������ʼ����ʾʱִ��
		virtual void OnHide(){};	//�����������ʱִ��
		virtual void OnUpdate(){};	//�������Ҫ�����߼�ʱִ��

		virtual void OnDraw3DReady(){};	//��׼������3Dʱִ��
		virtual void OnDraw3D(){};	//�������Ҫ����3Dʱִ��
		virtual void OnDraw3DFinished(){};	//��3D������ɺ�

        virtual void OnDraw2DReady(){};	//��׼������2D���ʱִ��
		virtual void OnDraw2D(){};	//�������Ҫ����2D���ʱִ��
		virtual void OnDraw2DFinished(){};	//��2D���������ɺ�

        virtual void OnDrawSceneReady(){};    //����������׼����ʼʱ
		virtual void OnDrawScene(){}; //�����Ƴ���ʱ
		virtual void OnDrawSceneFinished(){}; //���������ƽ���ʱ
		/* ��������
		 * ��������ص���2D��3D��������ֻ����������ƺ�����������Scene���ƺ�����
		 * ��������ص��ǳ�����������Ϊһ��������л��ƣ�Ȼ��Ѹó������Ƶõ���ͼ����Ϊ֡���棬�ٴε��ó������ƺ�����
		 */

		/* ������Ҫ���г�ʱִ��
		 * @param timeLimited ʱ�����ƣ�֡��
		 */
		virtual void OnFadeSwitchOut(int timeLimited){};

		/* ���������г�ʱ�����ӵ������߼�
		 * @param finished ʱ��ʣ��ٷֱ�
		 */
		virtual void OnFadeSwitchOutUpdate(float finished){};

		/* ������Ҫ������ʱִ��
		 * @param timeLimited ʱ�����ƣ�֡��
		 */
		virtual void OnFadeSwitchIn(int timeLimited){};

		/* ������������ʱ�����ӵ������߼�
		 * @param finished ʱ��ʣ��ٷֱ�
		 */
		virtual void OnFadeSwitchInUpdate(float finished){};

		/* ȡ���������
		 * @result �����
		 */
        virtual std::string GetName() const = 0;

        /* �������Ʒ������
         * @param name �����
         * @result ���
         */
        static std::shared_ptr<IComponent> GetComponent(const std::string name);
	};

}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��28�գ�
 * ���� �����������
 */
