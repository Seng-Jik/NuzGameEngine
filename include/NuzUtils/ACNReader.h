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
            PushAndCreateNode = 0x00,  //����ǰ�ڵ�ָ��ѹջ���ڵ�ǰ�ڵ��´���һ���µĽڵ㣬���½ڵ���Ϊ��ǰ�ڵ㣬����Ϊ�ڵ���
            Pop = 0x01,    //����ջ���Ľڵ�ָ��Ϊ��ǰ�ڵ�ָ�룬������ջ��������������
            CreateVar = 0x10,  //Ϊ��ǰ�ڵ㴴��һ�����ԣ�����Ϊ��������������Ϊ��ǰ����
            AddVal = 0x11,  //Ϊ��ǰ��������һ��ֵ������Ϊֵ
            End = 0xFF //������������������
        };

        /* ȡ��һ��ָ��ָ��
         * @param ָ�����
         * @result ָ��
         */
        virtual ACNOpr GetOpr(std::string& arg) noexcept = 0;

        /* ��ͷ���¶�ȡָ��ָ��
         */
        virtual void Reset() noexcept = 0;

        /* ���ļ�����ACN�ļ���ȡ��
         * @param path ACN�ļ�·��
         * @result ACN�ļ���ȡ��
         */
        static std::shared_ptr<IACNReader> CreateACNReader(const std::string& path);
	};
}

/* ������־��
 * 2016��5��4�գ�
 * ���� ����
 */