#pragma once
#include "../Component.h"
#include <memory>
#include <string>

namespace Nuz{

	/* 3Dģ�����
	* ʵ��2Dͼ��Ļ��ơ�
	*/
	class IModel3D:public IComponent{
	public:
		/* ʹ��ģ��
		 * @param 3Dģ��·��
		 */
		virtual void UseModel(const std::string&) = 0;

		/* ʹ��2Dͼ������һ��3D�ռ���ı��Σ�
		* @param path ͼ���ļ�
		* @param num ͼ����
		*/
		virtual void UseImage2D(const std::string& path,int num = 0) = 0;

		/* ʹ���ı�������һ��3D�ռ���ı��Σ�
		 * @param fontPath ����·��
		 * @param text �ı�
		 * @param size �����С
		 */
		virtual void UseText2D(const std::string& fontPath,const std::wstring& text,int size) = 0;

		/* �ͷ�ģ��
		*/
		virtual void FreeModel() = 0;

		/* ����ģ�͵�����λ��
		 * @param x xλ��
		 * @param y yλ��
		 * @param z zλ��
		 */
		virtual void SetPos(float x,float y) = 0;

		/* �����Ƿ���ʾ
		 * @param �Ƿ���ʾ
		 */
		virtual void SetVisible(bool) = 0;

		/* ������ת
		 * @param x ��ת����x
		 * @param y ��ת����y
		 * @param angle ��ת�Ƕ�
		 * @param yFlip �Ƿ���y����ת
		 * @param xFlip �Ƿ���x����ת
		 */
		virtual void SetRotate(float x,float y,float angle,bool yFlip,bool xFlip) = 0;

		/* ��������
		 * @param x x��������
		 * @param y y��������
		 * @param z z��������
		 */
		virtual void SetZoom(float x,float y,float z) = 0;

		/* �ڵ�ǰ����������
		 * @param x x��������
		 * @param y y��������
		 * @param z z��������
		 */
		 virtual void Zoom(float x,float y,float z) = 0;

        /* ����һ��3Dģ�����
         * @param name �������
         * @result ģ�����
         */
        static std::shared_ptr<IModel3D> CreateModel3D(const std::string& name);
	};
}
/* ������־��
 * 2016��4��20�գ�
 * ���� ����
 * 2016��4��28�գ�
 * ���� ��������
 */
