#pragma once
#include <memory>

namespace Nuz{
	class IKeyboard;

	/* �˴���������СNuz��Χ */
	#ifdef NUZ_VER_FULL
	class IGamePad;
	#endif

	/* �����豸������
	 * ����������е������豸
	 */
	class IInputDevieManager{
	public:

		/* ��ȡ���̿�����
		 * @result ���̿�����ָ�루�����̲�����ʱΪnullptr��
		 */
		virtual IKeyboard& GetKeyboard() const = 0;

		/* �˴���������СNuz��Χ */
		#ifdef NUZ_VER_FULL

		/* ��ȡ�����ֱ�����
		 * @result �ֱ�����
		 */
		virtual int GetGamePadNum() const = 0;

		/* ��ȡ�����ֱ�
		 * @param �ֱ����
		 * @result �ֱ�ʵ��
		 */
		 virtual IGamePad& GetGamePad(int) const = 0;
		#endif
	};
}

/* ������־��
 * 2016��4��17�գ�
 * ���� ����
 *
 */
