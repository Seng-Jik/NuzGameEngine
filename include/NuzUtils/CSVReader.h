#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* CSV�Ķ���
	 */
	class ICSVReader{
	public:

		/* �ڵ�ǰ�е���һ���ַ���
         * @throw std::runtime_error
		 * @result �ַ���
		 */
		virtual std::string PopString() = 0;

		/* �ڵ�ǰ�е���һ��float
         * @throw std::runtime_error
		 * @result ������float
		 */
		virtual float PopFloat() = 0;

		/* �ڵ�ǰ�е���һ��double
         * @throw std::runtime_error
		 * @result ������double
		 */
		virtual double PopDouble() = 0;

		/* �ڵ�ǰ�е���һ��int
         * @throw std::runtime_error
		 * @result ������int
		 */
		virtual int PopInt() = 0;

		/* �����Ƿ����
		 * @result �Ƿ����
		 */
		virtual bool LineEnd() = 0;

		/* �л�����һ��
         * @throw std::runtime_error
		 * @result �����Ƿ������һ��
		 */
		virtual bool NextLine() = 0;

		/* �����Ƿ������һ��
		 * @result �����Ƿ������һ��
		 */
		virtual bool IsLastLine() = 0;

		/* �ص���һ�еĵ�һ��Ԫ�ش����¿�ʼ */
		virtual void Reset() = 0;

	};

	/* ����CSV�Ķ���
	 * @param CSV�ļ�
	 * @throw std::runtime_error
	 * @result CSV�Ķ���
	 */
	std::shared_ptr<ICSVReader> CreateCSVReader(const std::string& path);
}

/* ������־��
 * 2016��4��19�գ�
 * ���� ����
 */
