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
         * @throw CannotMountFileSource �������ʱ�����򱨳��쳣
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

        /* �쳣�ࣺ������ļ�����ʽ */
        class InvalidFileName:public std::invalid_argument{
        public:
            inline InvalidFileName(const std::string& s):std::invalid_argument(s){};
        };

        /* �쳣�ࣺ�޷����ļ� */
        class CannotOpenFile:public std::runtime_error{
        public:
            inline CannotOpenFile(const std::string& s):std::runtime_error(s){};
        };

        /* �쳣�ࣺ�޷���������Դ */
        class CannotMountFileSource:public std::runtime_error{
        public:
            inline CannotMountFileSource(const std::string& s):std::runtime_error(s){};
        };
	};
}

/* ������־��
 * 2016��4��17�գ�
 * ���� ����
 * 2016��4��21�գ�
 * ���� ������Դģ��
 * 2016��4��24�գ�
 * ���� �ƶ��쳣��
 */
