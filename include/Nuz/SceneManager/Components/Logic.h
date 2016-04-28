#pragma once
#include "../Component.h"

namespace Nuz{

	/* �߼����
	 * ʵ���߼�
	 */
	class ILogic:public IComponent{
	public:
	    /* ����ʱע��
	     * ����һ��������ƣ����../IComponent.h
	     * @param name �������
	     */
	    using IComponent::IComponent;
		void OnInit() override{};	//����ʼ�����ʱִ��
        void OnQuit() override{};	//�����������ʹ��ʱִ��
        void OnShow() override{};	//�������ʼ����ʾʱִ��
        void OnHide() override{};	//�����������ʱִ��
        void OnUpdate() override{};	//�������Ҫ�����߼�ʱִ��

		/* ������Ҫ���г�ʱִ��
		 * @param ʱ�����ƣ�֡��
		 */
        void OnFadeSwitchOut(int timeLimited) override{};

		/* ���������г�ʱ�����ӵ������߼�
		 * @param ʱ��ʣ��ٷֱ�
		 */
        void OnFadeSwitchOutUpdate(float finished) override{};

		/* ������Ҫ������ʱִ��
		 * @param ʱ�����ƣ�֡��
		 */
        void OnFadeSwitchIn(int timeLimited) override{};

		/* ������������ʱ�����ӵ������߼�
		 * @param ʱ��ʣ��ٷֱ�
		 */
        void OnFadeSwitchInUpdate(float finished) override{};
	};
}
/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��27�գ�
 * ���� �޸�Ϊoverride��ʽ
 * 2016��4��28�գ�
 * ���� ��������
 */
