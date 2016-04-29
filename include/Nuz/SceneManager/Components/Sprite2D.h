#pragma once
#include "../Component.h"
#include <memory>
#include <string>

namespace Nuz{

	/* 2D�������
	* ʵ��2Dͼ��Ļ��ơ�
	*/
	class ISprite2D:public IComponent{
	public:
		/* ʹ��ͼ��
		* @param path ͼ���ļ�
		* @param num ͼ����
		*/
		virtual void UseImage(const std::string& path,int num = 0) = 0;

		/* ʹ���ı�
		 * @param fontPath ����·��
		 * @param text �ı�
		 * @param size �����С
		 */
		virtual void UseText(const std::string& fontPath,const std::wstring& text,int size) = 0;

		/* �ͷ�ͼ��
		*/
		virtual void FreeImage() = 0;

		/* ����ֻʹ��һ����ͼ��
		* @param x ͼ�����Ͻ�xλ�ã�-1~1��
		* @param y ͼ�����Ͻ�yλ��(-1~1)
		* @param w ͼ��Ŀ�
		* @param h ͼ��ĸ�
		*/
		virtual void SetSrc(float x,float y,int w,int h) = 0;

		/* ����ֻʹ��һ����ͼ��
		* @param x ͼ�����Ͻ�xλ�ã����أ�
		* @param y ͼ�����Ͻ�yλ��(����)
		* @param w ͼ��Ŀ�
		* @param h ͼ��ĸ�
		*/
		virtual void SetSrc(int x,int y,int w,int h) = 0;

		/* ��ȡ��ǰͼ���ܴ�С
		* @param w ��
		* @param h ��
		*/
		virtual void GetSize(int& w,int& h) const = 0;

		/* ����ͼ����Ƶ�Ŀ������λ��
		* @param x ��ǰ�����xλ��
		* @param y ��ǰ�����yλ��
		*/
		virtual void SetPos(float x,float y) = 0;

		/* ����Ŀ��λ�õĴ�С
		* @param w ��ȣ����ʣ�
		* @param h �߶ȣ����ʣ�
		*/
		virtual void SetDstSize(float w,float h) = 0;

		/* ������ת
		 * @param x ��ת����x
		 * @param y ��ת����y
		 * @param angle ��ת�Ƕ�
		 * @param yFlip �Ƿ���y����ת
		 * @param xFlip �Ƿ���x����ת
		 */
		virtual void SetRotate(float x,float y,float angle,bool yFlip,bool xFlip) = 0;

        /* ����һ��2D�������
         * @param name �������
         * @result �������
         */
        static std::shared_ptr<ISprite2D> CreateSprite2D(const std::string& name ="");
	};
}
/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��28�գ�
 * ���� ��������
 */
