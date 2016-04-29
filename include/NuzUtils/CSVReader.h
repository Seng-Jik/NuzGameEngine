#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* CSV阅读器
	 * 非线程安全注意
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
		virtual bool LineEnd() const = 0;

		/* 切换到下一行
         * @throw ValueNotFound
		 * @result 此行是否不是最后一行
		 */
		virtual bool NextLine() = 0;

		/* 此行是否是最后一行
		 * @result 此行是否是最后一行
		 */
		virtual bool IsLastLine() const = 0;

		/* 回到第一行的第一个元素处重新开始 */
		virtual void Reset() = 0;

		/* 取得该CSV文件所在目录
		 * @result 目录
		 */
        virtual std::string GetCurrentDir() const = 0;

		/* 存储到高速读取的二进制文件中
		 * @param 文件名
		 * @throw IFileSystem::CannotOpenFile
		 * @throw IFileSystem::InvaildFileName
		 */
        virtual void SaveToFastReadFile(const std::string&) const = 0;

        /* 异常类：CSV中未找到对象 */
        class ValueNotFound:public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
        };

        /* 异常类：无效CSV */
        class InvalidCSV:public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
        };

        /* 创建CSV阅读器
         * @param path CSV文件
         * @throw IFileSystem::CannotOpenFile
         * @throw IFileSystem::InvaildFileName
         * @throw ICSVReader::InvalidCSV
         * @result CSV阅读器
         */
        static std::shared_ptr<ICSVReader> CreateCSVReader(const std::string& path);
	};
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 * 2016年4月22日：
 * 星翼 字节码加入
 * 2016年4月24日：
 * 星翼 增补异常
 */
