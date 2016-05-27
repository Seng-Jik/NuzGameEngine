#pragma once
#include <string>
#include <memory>
namespace Nuz {

	/* 字体 */
	class IFont {
	public:
		virtual ~IFont() {};

		/* 创建字体
		 * @param file 字体文件
		 * @param size 字体大小
		 */
		static std::shared_ptr<IFont> CreateFont(const std::string& file, int size = 32);
	};
}

/* 2016年5月27日
 * 星翼 初稿
 */