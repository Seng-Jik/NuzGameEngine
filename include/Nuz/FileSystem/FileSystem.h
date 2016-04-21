#pragma once
#include <string>
#include <memory>
#include <vector>
namespace Nuz{
	class IFileSource;

	/* 文件系统
	 * 提供对文件的读入，可以挂载数据源，使用虚拟磁盘。
	 * 路径参考Linux/Unix的路径格式。
	 */
	class IFileSystem{
	public:
		/* 挂载数据源
		 * @param name 数据源名称
		 * @param dir 挂载的目标路径
		 * @param source 数据源实例
		 * @throw runtime_error 如果挂载失败，则会在此弹出该异常
		 */
		virtual void Mount(
				const std::string& name,
				const std::string& dir,
				std::shared_ptr<IFileSource> source
		) = 0;

		/* 卸载数据源
		 * @param name 数据源名称
		 * @throw runtime_error 如果卸载失败，则在此弹出该异常
		 */
		virtual void Unmount(const std::string& name) = 0;

		/* 加载文件
		 * 它会把整个文件加载到内存中并返回一个已经被加载完的缓存区指针。
		 * @param path 文件路径
		 * @result 得到的文件的缓存区指针
		 */
		virtual std::shared_ptr<std::vector<unsigned char>> LoadFile(const std::string& name) = 0;
	};
}

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 * 2016年4月21日：
 * 星翼 简化数据源模型
 */
