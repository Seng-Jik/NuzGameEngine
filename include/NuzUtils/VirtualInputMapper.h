#pragma once
#include <memory>
#include <string>

namespace Nuz{
	enum class KeyCode;
	class IKeyboard;
	class IGamePad;
}

namespace NuzUtils{

	/* ���������
	 * ����һ����ά�����飨����ֵ��Χ��Ϊ-32768~32767��
	 * ���ڰ������ɰ󶨲�ͬ�����ֵ
	 * ����ҡ�ˣ����԰󶨵�X��Y����
	 * �������ʹ�������Ϊ���ʣ����ĵ�Ϊ(0,0)��
	 * ��֤������һ������
	 */
	class IVirtualInputMapper{
	public:

		/* ��ø����������
		 * @param �������
		 * @result ������ģ��
		 */
		virtual int GetX() = 0;	//X����
		virtual int GetY() = 0;	//Y����
		virtual int GetZ() = 0;	//Z����

		/* �����������
		 * @result ��������
		 */
		virtual int GetVectorNum() = 0;

		/* ������������
		 * @param ��������
		 */
		virtual void SetVectorNum(int) = 0;

		/* �󶨼��̰���������
		 * @param ����ָ��
		 * @param ���̰���
		 * @param vectorNum �������
		 * @param useX ռ��X����
		 * @param x ռ��ʱX��ֵ
		 * @param useY ռ��Y����
		 * @param y ռ��ʱY��ֵ
		 * @param useZ ռ��Z����
		 * @param z ռ��Z�����ֵ
		 */
		virtual void BindKeyboardKey(
			std::shared_ptr<IKeyboard>,
			KeyCode,
			int vectorNum,
			bool useX,int x,
			bool useY,int y,
			bool useZ,int z
		) = 0;

		/* ���ֱ�����������
		 * @param �ֱ�ָ��
		 * @param key �ֱ�����
		 * @param vectorNum �������
		 * @param useX ռ��X����
		 * @param x ռ��ʱX��ֵ
		 * @param useY ռ��Y����
		 * @param y ռ��ʱY��ֵ
		 * @param useZ ռ��Z����
		 * @param z ռ��Z�����ֵ
		 */
		virtual void BindGamePadKey(
			std::shared_ptr<IGamePad>,
			int key,
			int vectorNum,
			bool useX,int x,
			bool useY,int y,
			bool useZ,int z
		) = 0;

		/* ��ҡ�˻�ʮ�ּ���X��Y����
		 * @param ҡ�˻�ʮ�ּ�ָ��
		 * @param vectorNum �������
		 */
		virtual void BindJoystick(
			std::shared_ptr<IJoystick>,
			int vectorNum;
		) = 0;


        /* ���������豸
         * @param ��������
         * @result ���������豸
         */
        static std::shared_ptr<IVirtualInputMapper> CreateVirtualInputMapper(int);
	};
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 */
