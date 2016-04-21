#pragma once
#include <memory>
#include <string>
#include "../Component.h"

namespace Nuz{

	/* ��ɫ��
	 */
	class IShader:public IComponent{
	public:

		/* ��������ɫ��
		 */
		virtual void Use() = 0;

		/* ͣ�ø���ɫ��
		 */
		virtual void Unuse() = 0;

	};
	/* ������ɫ����������ɫ��ʵ��
	 * @param vert ������ɫ���ļ���
	 * @param frag ƬԪ��ɫ���ļ���
	 * @result ��ɫ��ʵ��
	 */
	std::shared_ptr<IShader> CreateShader(const std::string& vert,const std::string& frag);
}
/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 *
 */
