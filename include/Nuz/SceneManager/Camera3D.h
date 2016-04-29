#pragma once

namespace Nuz{

	/* 3D�����
	* ʵ��3Dͼ������Ķ�λ��
	*/
	/* Ĭ�ϵ������
	 * 45���ӽ�
	 * ��Ļ����Ϊ(0,0)
	 * ��Ļ���Ͻ�Ϊ(-1,-1)
	 * ��Ļ���½�Ϊ(1,1)
	 * ������Զ�����޽�Ϊ(-1~1)
	 * �Դ����ơ�
	 */
	class ICamera3D{
	public:

		/* ������������
		 * @param x ����x����
		 * @param y ����y����
		 * @param z ����z����
		 */
		virtual void SetCenter(float x,float y,float z) = 0;

		/* ���ô����ĵ�һ����Ե�ĵ�λ��С
		 * @param w �����С
		 * @param h �����С
		 * @param d ����Զ�����޽���С
		 */
		virtual void SetZoom(float w,float h,float d) = 0;

		/* �Ե�ǰ�����Ϊ��׼����
		 * @param w �����С����
		 * @param h �����С����
		 * @param d ����Զ�����޽���С����
		 */
		virtual void Zoom(float w,float h,float d) = 0;

		/* ��ת��ǰ�����
		 * @param angle �Ƕ�
		 * @param x ��ת������x����
		 * @param y ��ת������y����
		 * @param z ��ת������z����
		 */
		virtual void Rotate(float angle,float x,float y,float z);

		/* �Ե�ǰ�����Ϊ��׼����ƽ��
		 * @param x �ƶ���x��
		 * @param y �ƶ���y��
		 * @param z �ƶ���z��
		 */
		virtual void Move(float x,float y,float z);

		/* �����������Ұ�Ƕ�
		 * @param �Ƕ�
		 */
		virtual void SetFov(float) = 0;

        /* ����һ��3D�����
         * @result �����
         */
        static std::shared_ptr<ICamera3D> CreateCamera3D();
	};
}
/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��28�գ�
 * ���� �ƶ�������������������
 * ���� ���������
 */
