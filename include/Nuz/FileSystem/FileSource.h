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
	    virtual ~IFileSource(){};

		/* ��ȡ�ļ�
		 * �ṩһ����ͷΪ/���ļ�·��
		 * �������ȡ�ļ������ء�
		 * ���û������ļ����뷵��nullptr�����Բ�������size
		 * @param path �ļ�·��
		 * @throw CannotOpenFile ����޷������ļ����뵯�����쳣
		 * @result ���ظ�������ļ����������������ʧ���뷵��nullptr.
		 */
		virtual std::shared_ptr<std::vector<uint8_t> > ReadFile(const std::string& path) const = 0;
	};
}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��21�գ�
 * �����쳣
 */
