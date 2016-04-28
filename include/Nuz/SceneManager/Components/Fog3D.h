#pragma once
#include "../Component.h"
#include <memory>

namespace Nuz{

	/* ����
	*/
	class IFog3D:public IComponent{
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
		 * @param z z����
		 * @param f ��ǿ��
		 */
		virtual void SetFogWalls(
			float x,
			float y,
			float z,
			float f
		) = 0;

		/* ����Ϊȫ����Ĭ�ϣ��ᶪʧ�Ѱ󶨵�����������
		*/
		virtual void SetGlobal() = 0;

        /* ����һ���������
         * @param name �����
         * @result �������
         */
        static std::shared_ptr<IFog3D> CreateFog3D(const std::string& name);
	};
}
/* ������־��
 * 2016��4��20�գ�
 * ���� ����
 * 2016��4��28�գ�
 * ���� �ƶ�������������������
 */
