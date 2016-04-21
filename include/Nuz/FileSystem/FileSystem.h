#pragma once
#include <string>
#include <memory>
#include <vector>
namespace Nuz{
	class IFileSource;

	/* �ļ�ϵͳ
	 * �ṩ���ļ��Ķ��룬���Թ�������Դ��ʹ��������̡�
	 * ·���ο�Linux/Unix��·����ʽ��
	 */
	class IFileSystem{
	public:
		/* ��������Դ
		 * @param name ����Դ����
		 * @param dir ���ص�Ŀ��·��
		 * @param source ����Դʵ��
		 * @throw runtime_error �������ʧ�ܣ�����ڴ˵������쳣
		 */
		virtual void Mount(
				const std::string& name,
				const std::string& dir,
				std::shared_ptr<IFileSource> source
		) = 0;

		/* ж������Դ
		 * @param name ����Դ����
		 * @throw runtime_error ���ж��ʧ�ܣ����ڴ˵������쳣
		 */
		virtual void Unmount(const std::string& name) = 0;

		/* �����ļ�
		 * ����������ļ����ص��ڴ��в�����һ���Ѿ���������Ļ�����ָ�롣
		 * @param path �ļ�·��
		 * @result �õ����ļ��Ļ�����ָ��
		 */
		virtual std::shared_ptr<std::vector<unsigned char>> LoadFile(const std::string& name) = 0;
	};
}

/* ������־��
 * 2016��4��17�գ�
 * ���� ����
 * 2016��4��21�գ�
 * ���� ������Դģ��
 */
