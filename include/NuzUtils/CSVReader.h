#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* CSV�Ķ���
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
		virtual bool LineEnd() = 0;

		/* �л�����һ��
         * @throw ValueNotFound
		 * @result �����Ƿ������һ��
		 */
		virtual bool NextLine() = 0;

		/* �����Ƿ������һ��
		 * @result �����Ƿ������һ��
		 */
		virtual bool IsLastLine() = 0;

		/* �ص���һ�еĵ�һ��Ԫ�ش����¿�ʼ */
		virtual void Reset() = 0;

		/* �洢�����ٶ�ȡ�Ķ������ļ���
		 * @param �ļ���
		 * @throw IFileSystem::CannotOpenFile
		 * @throw IFileSystem::InvaildFileName
		 */
        virtual void SaveToFastReadFile(const std::string&) = 0;

        /* �쳣�ࣺCSV��δ�ҵ����� */
        class ValueNotFound:public std::runtime_error{
        public:
            inline ValueNotFound(const std::string& s):std::runtime_error(s){};
        };
	};



	/* ����CSV�Ķ���
	 * @param path CSV�ļ�
     * @throw IFileSystem::CannotOpenFile
     * @throw IFileSystem::InvaildFileName
	 * @result CSV�Ķ���
	 */
	std::shared_ptr<ICSVReader> CreateCSVReader(const std::string& path);
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 * 2016��4��22�գ�
 * ���� �ֽ������
 * 2016��4��24�գ�
 * ���� �����쳣
 */
