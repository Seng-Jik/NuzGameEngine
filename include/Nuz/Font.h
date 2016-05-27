#pragma once
#include <string>
#include <memory>
namespace Nuz {

	/* ���� */
	class IFont {
	public:
		virtual ~IFont() {};

		/* ��������
		 * @param file �����ļ�
		 * @param size �����С
		 */
		static std::shared_ptr<IFont> CreateFont(const std::string& file, int size = 32);
	};
}

/* 2016��5��27��
 * ���� ����
 */