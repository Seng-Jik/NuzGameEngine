#pragma once
#include "Component.h"
#include <memory>

namespace Nuz{
	
	/* ��Դ
	 * û�й�Դʱ��ʹ�������Դ���ȫ�ֹ⡣
	 * �й�Դʱ�����治�ṩ��Դ��
	 */
	class ILight:public IComponent{
	public:
		/* �����ù�Դ
		 */
		virtual void Enable() = 0;
		
		/* �رոù�Դ
		 */
		virtual void Disable() = 0;
		
		/* ������ɫ����ԴĬ��Ϊ��ɫ������
		 * @param r ��
		 * @param g ��
		 * @param b ��
		 * @param a Alpha
		 */
		virtual void SetColor(float r,float g,float b,float a) = 0;
		
		/* ��������
		 * @param x x����
		 * @param y y����
		 * @param z z����
		 */
		virtual void SetPos(float x,float y,float z) = 0;
		
		/* ����Ϊ������ */
		virtual void SetAmbient() = 0;
		
		/* ����Ϊ����� */
		virtual void SetDiffuse() = 0;
	};
	
	/* ����һ����Դ
	 * @result ��Դ
	 */
	std::shared_ptr<ILight> CreateLight();
}
/* ������־��
 * 2016��4��20�գ�
 * ���� ����
 *
 */
