#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* CSV�Ķ���
	 * ���̰߳�ȫע��
	 */
	class ICSVReader{
	public:

		/* �ڵ�ǰ�е���һ���ַ���
         * @throw ValueNotFound
		 * @result �ַ���
		 */
		virtual std::string PopString() = 0;

		/* �ڵ�ǰ�е���һ��float
         * @throw ValueNotFound
		 * @result ������float
		 */
		virtual float PopFloat() = 0;

		/* �ڵ�ǰ�е���һ��double
         * @throw ValueNotFound
		 * @result ������double
		 */
		virtual double PopDouble() = 0;

		/* �ڵ�ǰ�е���һ��int
         * @throw ValueNotFound
		 * @result ������int
		 */
		virtual int PopInt() = 0;

		/* �����Ƿ����
		 * @result �Ƿ����
		 */
		virtual bool LineEnd() const = 0;

		/* �л�����һ��
         * @throw ValueNotFound
		 * @result �����Ƿ������һ��
		 */
		virtual bool NextLine() = 0;

		/* �����Ƿ������һ��
		 * @result �����Ƿ������һ��
		 */
		virtual bool IsLastLine() const = 0;

		/* �ص���һ�еĵ�һ��Ԫ�ش����¿�ʼ */
		virtual void Reset() = 0;

		/* ȡ�ø�CSV�ļ�����Ŀ¼
		 * @result Ŀ¼
		 */
        virtual std::string GetCurrentDir() const = 0;

		/* �洢�����ٶ�ȡ�Ķ������ļ���
		 * @param �ļ���
		 * @throw IFileSystem::CannotOpenFile
		 * @throw IFileSystem::InvaildFileName
		 */
        virtual void SaveToFastReadFile(const std::string&) const = 0;

        /* �쳣�ࣺCSV��δ�ҵ����� */
        class ValueNotFound:public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
        };

        /* �쳣�ࣺ��ЧCSV */
        class InvalidCSV:public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
        };

        /* ����CSV�Ķ���
         * @param path CSV�ļ�
         * @throw IFileSystem::CannotOpenFile
         * @throw IFileSystem::InvaildFileName
         * @throw ICSVReader::InvalidCSV
         * @result CSV�Ķ���
         */
        static std::shared_ptr<ICSVReader> CreateCSVReader(const std::string& path);
	};
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 * 2016��4��22�գ�
 * ���� �ֽ������
 * 2016��4��24�գ�
 * ���� �����쳣
 */
