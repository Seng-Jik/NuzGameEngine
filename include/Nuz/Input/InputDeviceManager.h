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
		virtual std::shared_ptr<IKeyboard> GetKeyboard() = 0;

		/* �˴���������СNuz��Χ */
		#ifdef NUZ_VER_FULL

		/* ��ȡ�����ֱ�����
		 * @result �ֱ�����
		 */
		virtual int GetGamePadNum() = 0;

		/* ��ȡ�����ֱ�
		 * @param �ֱ����
		 * @result �ֱ�ʵ��
		 */
		 virtual std::shared_ptr<IGamePad> GetGamePad(int) = 0;
		#endif
	};
}

/* ������־��
 * 2016��4��17�գ�
 * ���� ����
 *
 */
