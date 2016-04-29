#pragma once
#include <string>
#include <memory>
#include <vector>
#include <cstdint>
namespace Nuz{
	class IFileSource;

	/* �ļ�ϵͳ
	 * �ṩ���ļ��Ķ��룬���Թ�������Դ��ʹ��������̡�
	 * ·���ο�Linux/Unix��·����ʽ��
	 */
	class IFileSystem{
	public:
		/* ��������Դ�����̰߳�ȫ��
		 * @param source ����Դʵ��
		 * @param dir ���ڵ���Ŀ¼�������紫��"mnt"�������ʱ������ԴĿ¼Ϊ"/mnt"��Ϊ����Ϊ��Ŀ¼��
         * @throw CannotMountFileSource �������ʱ�����򱨳��쳣
		 */
		virtual void Mount(const std::shared_ptr<const Nuz::IFileSource>& source,const std::string& dir = "") = 0;

		/* �����ļ�
		 * ����������ļ����ص��ڴ��в�����һ���Ѿ���������Ļ�����ָ�롣
		 * @param path �ļ�·��
		 * @throw InvalidFileName ��Ч���ļ���
		 * @throw CannotOpenFile �޷����ļ�
		 * @result �õ����ļ��Ļ�����ָ��
		 */
		virtual std::shared_ptr<std::vector<uint8_t>> LoadFile(const std::string& path) const = 0;

        /* ����һ��Ŀ¼·��������һ��Ŀ¼·��
         * ���߸���һ���ļ�������ļ�����һ��Ŀ¼
         * @param path ������Ŀ¼���ļ�
         * @throw IFileSystem::InvaildFileName
         * @result ��һ��Ŀ¼
         */
        static std::string GetUpperDir(const std::string& path);

        /* �쳣�ࣺ������ļ�����ʽ */
        class InvalidFileName:public std::invalid_argument{
        public:
            using std::invalid_argument::invalid_argument;
        };

        /* �쳣�ࣺ�޷����ļ� */
        class CannotOpenFile:public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
        };

        /* �쳣�ࣺ�޷���������Դ */
        class CannotMountFileSource:public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
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
 * 2016��4��27�գ�
 * ���� �ɹ��ص�һ��Ŀ¼
 */
