#pragma once
#include <memory>

namespace Nuz{
	class IJoystick;
	
	/* �ֱ������� */
	class IGamePad{
	public:
		/* ȡ�ð�������
		 * @result ��������
		 */
		virtual int GetButtonNums() = 0;
		
		/* ȡ�ð����Ƿ��Ѿ�����
		 * @param n �������
		 * @result �����Ƿ��Ѿ�����
		 */
		virtual bool KeyPressed(int n) = 0;
		
		/* ȡ���ֱ���ҡ�˻�ʮ�ּ�����
		 * @result ����
		 */
		virtual int GetJoystickNum() = 0;
		
		/* ȡ�õ�n��ҡ�˻�ʮ�ּ�
		 * @param n ҡ�˻�ʮ�ּ����
		 * @result ҡ�˻�ʮ�ּ�ʵ��
		 */
		virtual std::shared_ptr<IJoystick> GetJoystick() = 0;
	};
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 *
 */
