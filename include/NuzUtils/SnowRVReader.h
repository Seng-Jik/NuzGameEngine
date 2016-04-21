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
         * @throw std::runtime_error
		 * @result �����ַ���
		 */
		virtual std::string GetString(const std::string&) = 0;

		/* ȡ����ֵ����
		 * @param ������
         * @throw std::runtime_error
		 * @result ������ֵ
		 */
		virtual int GetInt(const std::string&) = 0;

		/* ȡ�ø���������
		 * @param ������
         * @throw std::runtime_error
		 * @result ����������
		 */
		virtual double GetFloat(const std::string&) = 0;
	};

	/* ����SnowRV�Ķ���
	 * @param RV�ļ�
     * @throw std::runtime_error
	 * @result RV�Ķ���
	 */
	std::shared_ptr<ISnowRVReader> CreateSnowRVReader(const std::string& path);
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 */
