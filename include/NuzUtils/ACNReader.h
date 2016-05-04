#pragma once
#include <memory>
#include <string>
#include <cstdint>

namespace NuzUtils{

	/* ACN���������ļ��Ķ���
	 */
	class IACNReader{
	public:
        /* ������ָ��ָ�� */
        /* �������Ķ���ָ�������� */
        /* ���ܻ��ж��������������������ļ������� */
        /* ���д��ȫ�Ĵ����������Ķ���ָ���������� */
        enum class ACNOpr{
            PushAndCreateNode = 0x00,  //����ǰ�ڵ�ָ��ѹջ������һ���µĽڵ㣬����Ϊ�ڵ���
            Pop = 0x01,    //����ջ���Ľڵ�ָ��Ϊ��ǰ�ڵ�ָ�룬������ջ��������Ϊ��
            CreateVar = 0x10,  //Ϊ��ǰ�ڵ㴴��һ�����ԣ�����Ϊ��������������Ϊ��ǰ����
            AddVal = 0x11,  //Ϊ��ǰ�������һ��ֵ
            End = 0xFF //����������
        };

        /* ȡ��һ��ָ��ָ��
         * @param ָ�����
         * @result ָ��
         */
        virtual ACNOpr GetOpr(std::string& arg) = 0;

        /* ��ͷ���¶�ȡָ��ָ��
         */
        virtual void Reset() = 0;
	};
}

/* ������־��
 * 2016��5��4�գ�
 * ���� ����
 */
