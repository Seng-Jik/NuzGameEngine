#pragma once
#include <string>
#include <memory>
#include <vector>
#include <cstdint>
namespace Nuz{
	class IFileSource;

	/* 文件系统
	 * 提供对文件的读入，可以挂载数据源，使用虚拟磁盘。
	 * 路径参考Linux/Unix的路径格式。
	 */
	class IFileSystem{
	public:
		/* 挂载数据源（非线程安全）
		 * @param source 数据源实例
		 * @param dir 挂在到的目录名（比如传入"mnt"，则访问时该数据源目录为"/mnt"，为空则为根目录）
         * @throw CannotMountFileSource 如果挂载时出错则报出异常
		 */
		virtual void Mount(const std::shared_ptr<const Nuz::IFileSource>& source,const std::string& dir = "") = 0;

		/* 加载文件
		 * 它会把整个文件加载到内存中并返回一个已经被加载完的缓存区指针。
		 * @param path 文件路径
		 * @throw InvalidFileName 无效的文件名
		 * @throw CannotOpenFile 无法打开文件
		 * @result 得到的文件的缓存区指针
		 */
		virtual std::shared_ptr<std::vector<uint8_t>> LoadFile(const std::string& path) const = 0;

        /* 给定一个目录路径，求上一层目录路径
         * 或者给定一个文件，求该文件的上一层目录
         * @param path 给定的目录或文件
         * @throw IFileSystem::InvaildFileName
         * @result 上一层目录
         */
        static std::string GetUpperDir(const std::string& path);

        /* 异常类：错误的文件名格式 */
        class InvalidFileName:public std::invalid_argument{
        public:
            using std::invalid_argument::invalid_argument;
        };

        /* 异常类：无法打开文件 */
        class CannotOpenFile:public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
        };

        /* 异常类：无法挂载数据源 */
        class CannotMountFileSource:public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
        };
	};
}

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 * 2016年4月21日：
 * 星翼 简化数据源模型
 * 2016年4月24日：
 * 星翼 移动异常类
 * 2016年4月27日：
 * 星翼 可挂载到一级目录
 */
