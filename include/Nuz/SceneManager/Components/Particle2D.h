#pragma once
#include "../Component.h"
#include <string>
#include <functional>

namespace NuzUtil{

	/* �������� */
	class IDot2D{
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
		 * @result �Ƕ�
		 */
		virtual float GetAngle() = 0;

		/* ���ýǶ�
		 * @param a �Ƕ�
		 */
		virtual void SetAngle(float a) = 0;

		/* �ڵ�ǰ���������ӽǶ�
		 * @param �Ƕ�
		 */
		virtual void AddAngle(float a) = 0;

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
		 */
		virtual void GetPos(float& x,float& y) = 0;

		/* ȡ������ʱ����֡��
		 * @result ֡��
		 */
		virtual unsigned long GetLife() = 0;

		/* ɱ��������
		 */
		virtual void Kill() = 0;
	};

	/* 2D������� */
	class IParticle2D{
	public:

		/* �����Ӵ�����
		 * ���Ӵ�����ÿ֡�������ÿ������
		 * ����Դ�����Щ���ӵ���Ϊ
		 * @param Ҫ�󶨵����Ӵ�����
		*/
		virtual void BindFunction(std::function<void(IParticle2D&,IDot2D&)>) = 0;

		/* �������
		 * �����ӻ����̱����Ӵ���������
		 */
		virtual void AddDot() = 0;
	};

	/* ����2D����ϵͳ
	 * @result 2D����ϵͳ
	 */
	std::shared_ptr<IParticle2D> CreateParticle2D();
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 *
 */
