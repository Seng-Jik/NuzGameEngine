#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* CSV阅读器
	 */
	class ICSVReader{
	public:

		/* 在当前行弹出一个字符串
         * @throw std::runtime_error
		 * @result 字符串
		 */
		virtual std::string PopString() = 0;

		/* 在当前行弹出一个float
         * @throw std::runtime_error
		 * @result 弹出的float
		 */
		virtual float PopFloat() = 0;

		/* 在当前行弹出一个double
         * @throw std::runtime_error
		 * @result 弹出的double
		 */
		virtual double PopDouble() = 0;

		/* 在当前行弹出一个int
         * @throw std::runtime_error
		 * @result 弹出的int
		 */
		virtual int PopInt() = 0;

		/* 此行是否结束
		 * @result 是否结束
		 */
		virtual bool LineEnd() = 0;

		/* 切换到下一行
         * @throw std::runtime_error
		 * @result 此行是否不是最后一行
		 */
		virtual bool NextLine() = 0;

		/* 此行是否是最后一行
		 * @result 此行是否是最后一行
		 */
		virtual bool IsLastLine() = 0;

		/* 回到第一行的第一个元素处重新开始 */
		virtual void Reset() = 0;

	};

	/* 创建CSV阅读器
	 * @param CSV文件
	 * @throw std::runtime_error
	 * @result CSV阅读器
	 */
	std::shared_ptr<ICSVReader> CreateCSVReader(const std::string& path);
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 */
