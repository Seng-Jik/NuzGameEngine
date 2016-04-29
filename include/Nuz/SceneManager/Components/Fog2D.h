#pragma once
#include "../Component.h"
#include <memory>

namespace Nuz{

	/* 2D����
	*/
	class IFog2D:public IComponent{
	public:
		/* ʹ����ɫ��Ĭ�ϰ�ɫ��
		* @param r ��
		* @param g ��
		* @param b ��
		*/
		virtual void SetColor(float r,float g,float b) = 0;

		/* ����������������ô˲�����������Ϊ���������Ҫ�������󶨲��ܱ�������
		 * @param x x����
		 * @param y y����
		 * @param f ��ǿ��
		 */
		virtual void SetFogWalls(
			float x,
			float y,
			float f
		) = 0;

		/* ����Ϊȫ����Ĭ�ϣ��ᶪʧ�Ѱ󶨵�����������
		*/
		virtual void SetGlobal() = 0;

        /* ����һ���������
         * @param name �����
         * @result �������
         */
        static std::shared_ptr<IFog2D> CreateFog2D(const std::string& name = "");
	};
}
/* ������־��
 * 2016��4��20�գ�
 * ���� ����
 * 2016��4��28�գ�
 * ���� �ƶ�������������������
 */
