#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* CSV阅读器
	 */
	class ICSVReader{
	public:

		/* 在当前行弹出一个字符串
         * @throw ValueNotFound
		 * @result 字符串
		 */
		virtual std::string PopString() = 0;

		/* 在当前行弹出一个float
         * @throw ValueNotFound
		 * @result 弹出的float
		 */
		virtual float PopFloat() = 0;

		/* 在当前行弹出一个double
         * @throw ValueNotFound
		 * @result 弹出的double
		 */
		virtual double PopDouble() = 0;

		/* 在当前行弹出一个int
         * @throw ValueNotFound
		 * @result 弹出的int
		 */
		virtual int PopInt() = 0;

		/* 此行是否结束
		 * @result 是否结束
		 */
		virtual bool LineEnd() = 0;

		/* 切换到下一行
         * @throw ValueNotFound
		 * @result 此行是否不是最后一行
		 */
		virtual bool NextLine() = 0;

		/* 此行是否是最后一行
		 * @result 此行是否是最后一行
		 */
		virtual bool IsLastLine() = 0;

		/* 回到第一行的第一个元素处重新开始 */
		virtual void Reset() = 0;

		/* 存储到高速读取的二进制文件中
		 * @param 文件名
		 * @throw IFileSystem::CannotOpenFile
		 * @throw IFileSystem::InvaildFileName
		 */
        virtual void SaveToFastReadFile(const std::string&) = 0;

        /* 异常类：CSV中未找到对象 */
        class ValueNotFound:public std::runtime_error{
        public:
            inline ValueNotFound(const std::string& s):std::runtime_error(s){};
        };
	};



	/* 创建CSV阅读器
	 * @param path CSV文件
     * @throw IFileSystem::CannotOpenFile
     * @throw IFileSystem::InvaildFileName
	 * @result CSV阅读器
	 */
	std::shared_ptr<ICSVReader> CreateCSVReader(const std::string& path);
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 * 2016年4月22日：
 * 星翼 字节码加入
 * 2016年4月24日：
 * 星翼 增补异常
 */
