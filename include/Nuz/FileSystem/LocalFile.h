#pragma once
#include "FileSource.h"

namespace Nuz{
	/* �ļ�����Դ
	 * ��ɸ������Թ��ص������ļ�ϵͳ�ϡ�
	 * ����Ҫ�ֶ���������
	 */
	class ILocalFile:virtual public IFileSource{
	public:
		/* ��ȡ�ļ�
		 * �ṩһ����ͷΪ/���ļ�·��
		 * �������ȡ�ļ������ء�
		 * ���û������ļ����뷵��nullptr�����Բ�������size
		 * @param path �ļ�·��
		 * @param size ���ظ�������ļ���С���ֽ�����
         * @throw std::invalid_argument
		 * @throw std::runtime_error
		 * @result ���ظ�������ļ����������������ʧ���뷵��nullptr.
		 */
		virtual std::shared_ptr<std::vector<unsigned char> > ReadFile(const std::string& path,unsigned long& size) const = 0;

		/* ȡ�ļ���С
		 * @param path �ļ���
         * @throw std::invalid_argument
		 * @throw std::runtime_error
		 * @result �ļ���С���ֽ�����
		 */
		virtual unsigned long GetFileSize(const std::string& path) const = 0;

		/* ���滺�������ļ�
		 * @param ������ָ��
		 * @param path �ļ���
         * @throw std::invalid_argument
		 * @throw std::runtime_error
		 */
		virtual void SaveFile(const std::shared_ptr<std::vector<unsigned char> >,const std::string path) const = 0;

		/* �����ļ�
		 * @param src ��Դ�ļ�
		 * @param dst Ŀ���ļ�
		 * @throw std::invalid_argument
		 * @throw std::runtime_error
		 */
		virtual void CopyFile(const std::string& src,const std::string& dst) const = 0;

	};
}

/* ������־��
 * 2016��4��18�գ�
 * ���� ����
 * 2016��4��21�գ�
 * ���� ɾ��DeleteFile�������쳣
 */
