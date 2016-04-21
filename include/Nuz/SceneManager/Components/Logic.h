#pragma once
#include "Component.h"

namespace Nuz{
	
	/* �߼����
	 * ʵ���߼�
	 */
	class ILogic:public IComponent{
	public:
		virtual void OnInit(){};	//����ʼ�����ʱִ��
		virtual void OnQuit(){};	//�����������ʹ��ʱִ��
		virtual void OnShow(){};	//�������ʼ����ʾʱִ��
		virtual void OnHide(){};	//�����������ʱִ��
		virtual void OnUpdate(){};	//�������Ҫ�����߼�ʱִ��
		
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
	};
}
/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 *
 */
