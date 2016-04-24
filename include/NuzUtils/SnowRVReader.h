#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* SnowRV�Ķ���
	 */
	class ISnowRVReader{
	public:

		/* ȡ���ַ�������
		 * @param ������
         * @throw ValueNotFound
		 * @result �����ַ���
		 */
		virtual std::string GetString(const std::string&) = 0;

		/* ȡ����ֵ����
		 * @param ������
         * @throw ValueNotFound
		 * @result ������ֵ
		 */
		virtual int GetInt(const std::string&) = 0;

		/* ȡ�ø���������
		 * @param ������
         * @throw ValueNotFound
		 * @result ����������
		 */
		virtual double GetFloat(const std::string&) = 0;

		/* �洢Ϊ���Կ��ٶ�ȡ�Ķ�������
		 * @param �ļ���
         * @throw IFileSystem::CannotOpenFile
         * @throw IFileSystem::InvaildFileName
         */
        virtual void SaveToFastReadFile(const std::string&) = 0;

        /* �쳣�ࣺ�����SnowRV */
        class SnowRVCompileFailed:public std::runtime_error{
        public:
            inline SnowRVCompileFailed(const std::string& s):std::runtime_error(s){};
        };

        /* �쳣�ࣺSnowRV��δ�ҵ���Ӧ���� */
        class ValueNotFound:public std::runtime_error{
        public:
            inline ValueNotFound(const std::string& s):std::runtime_error(s){};
        };
	};

	/* ����SnowRV�Ķ���
	 * @param RV�ļ�
     * @throw ISnowRVReader::SnowRVCompileFailed
     * @throw IFileSystem::CannotOpenFile
     * @throw IFileSystem::InvaildFileName
	 * @result RV�Ķ���
	 */
	std::shared_ptr<ISnowRVReader> CreateSnowRVReader(const std::string& path);
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 * 2016��4��22�գ�
 * ���� �ֽ������
 * 2016��4��24�գ�
 * ���� �����쳣
 */
