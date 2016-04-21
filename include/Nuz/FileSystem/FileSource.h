#pragma once
#include <memory>
#include <string>
#include <vector>
namespace Nuz{
	/* �ļ�����Դ
		��ɸ������Թ��ص������ļ�ϵͳ�ϡ�
	 */
	class IFileSource{
	public:
		/* ��ȡ�ļ�
		 * �ṩһ����ͷΪ/���ļ�·��
		 * �������ȡ�ļ������ء�
		 * ���û������ļ����뷵��nullptr�����Բ�������size
		 * @param path �ļ�·��
		 * @param size ���ظ�������ļ���С���ֽ�����
         * @throw std::invalid_argument ���������ļ�����ʽ�����⣬�뵯�����쳣
		 * @throw std::runtime_error ����޷������ļ����뵯�����쳣
		 * @result ���ظ�������ļ����������������ʧ���뷵��nullptr.
		 */
		virtual std::shared_ptr<std::vector<unsigned char> > ReadFile(const std::string& path,unsigned long& size) = 0;
	};
}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��21�գ�
 * �����쳣
 */
