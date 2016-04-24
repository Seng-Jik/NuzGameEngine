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

		/* ������ɫ����Uniform Float����
		 * @param uniform uniform������
		 * @param ��Щ���Ǳ�������Ϊ�������ж��floatֵ
		 */
		virtual SetUniformFloat(const std::string& uniform,float,float = 0,float = 0,float = 0,float = 0) = 0;

        /* ������ɫ����Uniform Int����
		 * @param uniform uniform������
		 * @param ��Щ���Ǳ�������Ϊ�������ж��intֵ
		 */
		virtual SetUniformFloat(const std::string& uniform,int,int = 0,int = 0,int = 0,int = 0) = 0;

		/* ��ɫ����� */
		typedef int ShaderHandle;

		/* ��ȡHandle��������в�����ɫ��
		 * @result Handle
		 */
        virtual ShaderHandle GetHandle() = 0;
	};
	/* ���ļ�������ɫ����������ɫ��ʵ��
	 * @param vert ������ɫ���ļ���
	 * @param frag ƬԪ��ɫ���ļ���
	 * @result ��ɫ��ʵ��
	 */
	std::shared_ptr<IShader> CreateShaderFromFile(const std::string& vert,const std::string& frag);

	/* ���ַ���������ɫ����������ɫ��ʵ��
	 * @param vert ������ɫ���ļ���
	 * @param frag ƬԪ��ɫ���ļ���
	 * @result ��ɫ��ʵ��
	 */
	std::shared_ptr<IShader> CreateShaderFromString(const std::string& vert,const std::string& frag);
}
/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 * 2016��4��24�գ�
 * ���� ��ӷ���SetUniformFloat��SetUniformInt��
 * ���� ������ַ���������ɫ����
 * ���� ����ȡ��ShaderHandle��
 */
