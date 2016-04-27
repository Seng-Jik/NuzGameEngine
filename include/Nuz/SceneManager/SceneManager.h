#pragma once
#include <cstdint>
namespace Nuz{
	class IScene;
	/* Nuz����������
	* �ƶ�������Ϸ��������
	*/
	class ISceneManager{
	public:
		/* ����һ��������ֻ������������Ϸʱ��������
		 * @param ��Ҫ�����ĳ���
		 */
		virtual void Start(IScene&) = 0;

		/* ƽ���л���һ�����������л���Ч��
		 * �л���Ч�ɳ����ṩ��
		 * @param Ҫ��ת���ĳ���
		 * @param time �����л�ʱ��
		 */
		virtual void FadeTo(IScene&,uint32_t time) = 0;

		/* �����˳�����������Start()������
		 */
		virtual void Exit() = 0;
	};
}

/* ������־��
 * 2016��4��17�գ�
 * ���� ����
 *
 */
