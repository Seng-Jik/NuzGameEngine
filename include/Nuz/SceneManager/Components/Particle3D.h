#pragma once
#include "../Component.h"
#include <string>
#include <functional>
#include <memory>

namespace Nuz{

	/* �������� */
	class IDot3D{
	public:
		/* ʹ��һ����������
		 * @param �ļ�
		 */
		virtual void UseImage(const std::string&) = 0;

		/* ��ʹ����������
		 * ʹ��һ����ɫ�ĵ����
		 */
		virtual void UnuseImage() = 0;

		/* �����ٶ�
		 * @param s �ٶ�
		 */
		virtual void SetSpeed(float s) = 0;

		/* �ڵ�ǰ�����������ٶ�
		 * @param s �ٶ�
		 */
		virtual void AddSpeed(float s) = 0;

		/* ȡ���ٶ�
		 * @result �ٶ�
		 */
		virtual float GetSpeed() = 0;

		/* ����͸����
		 * @param a ͸����
		 */
		virtual void SetAlpha(float a) = 0;

		/* ��ǰ����������͸����
		 * @param a ͸����
		 */
		virtual void AddAlpha(float a) = 0;

		/* ��ȡ͸����
		 * @result ͸����
		 */
		virtual float GetAlpha() = 0;

		/* ��ȡ��ǰ�Ƕ�
		 * ����ʹ��һ����ά������ʾ
		 * @param a ����x����
		 * @param b ����y����
		 * @param c ����z����
		 */
		virtual void GetAngle(float& a,float& b,float& c) = 0;

		/* ���ýǶ�
		 * ����ʹ��һ����ά������ʾ
		 * @param a ����x����
		 * @param b ����y����
		 * @param c ����z����
		 */
		virtual void SetAngle(float a,float b,float c) = 0;

		/* �ڵ�ǰ���������ӽǶ�
		 * ����ʹ��һ����ά������ʾ
		 * @param a ����x����
		 * @param b ����y����
		 * @param c ����z����
		 */
		virtual void AddAngle(float a,float b,float c) = 0;

		/* ����״̬
		 * �����û��Զ���
		 * @param n Ҫָ����״̬��
		 * @param status ״̬
		 */
		virtual void SetStatus(int n,float status) = 0;

		/* ��ȡ״̬
		 * �����û��Զ���
		 * @param n ״̬��
		 * @result ״̬
		 */
		virtual float GetStatus(int n) = 0;

		/* ����������ɫ����
		 * @param r ��(0~1)
		 * @param g ��(0~1)
		 * @param b ��(0~1)
		 */
		virtual void SetRGB(float r,float g,float b) = 0;

		/* ȡ��������ɫ����
		 * @param r ��(0~1)
		 * @param g ��(0~1)
		 * @param b ��(0~1)
		 */
		virtual void GetRGB(float& r,float& g,float& b) = 0;

		/* �ڵ�ǰ���������ӹ�����
		 * @param r ��(�Ӻ���0~1֮��)
		 * @param g ��(�Ӻ���0~1֮��)
		 * @param b ��(�Ӻ���0~1֮��)
		 */
		virtual void AddRGB(float r,float g,float b) = 0;

		/* ��ȡ��������
		 * @param x xλ��
		 * @param y yλ��
		 * @param z zλ��
		 */
		virtual void GetPos(float& x,float& y,float& z) = 0;

		/* ȡ������ʱ����֡��
		 * @result ֡��
		 */
		virtual uint32_t GetLife() = 0;

		/* ɱ��������
		 */
		virtual void Kill() = 0;
	};

	/* 2D������� */
	class IParticle3D{
	public:

		/* �����Ӵ�����
		 * ���Ӵ�����ÿ֡�������ÿ������
		 * ����Դ�����Щ���ӵ���Ϊ
		 * @param Ҫ�󶨵����Ӵ�����
		*/
		virtual void BindFunction(std::function<void(IParticle3D&,IDot3D&)>) = 0;

		/* �������
		 * �����ӻ����̱����Ӵ���������
		 */
		virtual void AddDot() = 0;
	};

	/* ����3D����ϵͳ
	 * @result 3D����ϵͳ
	 */
	std::shared_ptr<IParticle3D> CreateParticle3D();
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 *
 */
