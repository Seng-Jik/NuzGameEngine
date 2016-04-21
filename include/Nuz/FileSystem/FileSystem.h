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
		 * @param source ����Դʵ��
         * @throw runtime_error �������ʱ�����򱨳��쳣
		 */
		virtual void Mount(std::shared_ptr<IFileSource> source) = 0;

		/* �����ļ�
		 * ����������ļ����ص��ڴ��в�����һ���Ѿ���������Ļ�����ָ�롣
		 * @param path �ļ�·��
		 * @throw InvalidFileName ��Ч���ļ���
		 * @throw CannotOpenFile �޷����ļ�
		 * @result �õ����ļ��Ļ�����ָ��
		 */
		virtual std::shared_ptr<std::vector<unsigned char>> LoadFile(const std::string& path) const = 0;
	};
}

/* ������־��
 * 2016��4��17�գ�
 * ���� ����
 * 2016��4��21�գ�
 * ���� ������Դģ��
 */
