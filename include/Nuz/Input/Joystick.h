#pragma once

namespace Nuz{
	
	/* ҡ�˻�ʮ�ּ������� */
	class IJoystick{
	public:
	
		/* ȡ���ƶ����µ�X���������
		 * �����(-1)�����ұ�(1)
		 * @result X������
		 */
		virtual float GetX() = 0;
		
		/* ȡ���ƶ����µ�Y���������
		 * ���ϱ�(-1)�����±�(1)
		 * @result Y������
		 */
		virtual float GetY() = 0;
	};

}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 *
 */
