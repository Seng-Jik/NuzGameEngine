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
		virtual int GetButtonNums() const = 0;

		/* ȡ�ð����Ƿ��Ѿ�����
		 * @param n �������
		 * @result �����Ƿ��Ѿ�����
		 */
		virtual bool KeyPressed(int n) const = 0;

		/* ȡ���ֱ���ҡ�˻�ʮ�ּ�����
		 * @result ����
		 */
		virtual int GetJoystickNum() const = 0;

		/* ȡ�õ�n��ҡ�˻�ʮ�ּ�
		 * @param n ҡ�˻�ʮ�ּ����
		 * @result ҡ�˻�ʮ�ּ�ʵ��
		 */
		virtual IJoystick& GetJoystick() const = 0;
	};
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 *
 */
