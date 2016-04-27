#pragma once
#include <cstdint>
#include "FileSource.h"

namespace Nuz{
	/* 文件数据源
	 * 完成该类后可以挂载到虚拟文件系统上。
	 * 你需要手动挂载它。
	 */
	class ILocalFile:public IFileSource{
	public:
		/* 读取文件
		 * 提供一个开头为/的文件路径
		 * 从这里读取文件并返回。
		 * @param path 文件路径
         * @throw IFileSystem::InvalidFileName
		 * @throw IFileSystem::CannotOpenFile
		 * @result 返回给引擎的文件缓存区，如果加载失败请返回nullptr.
		 */
		std::shared_ptr<std::vector<uint8_t> > ReadFile(const std::string& path) const override = 0;

		/* 保存缓存区到文件
		 * @param 缓存区指针
		 * @param path 文件名
         * @throw IFileSystem::InvalidFileName
		 * @throw IFileSystem::CannotOpenFile
		 */
		virtual void SaveFile(const std::shared_ptr<std::vector<uint8_t> >,const std::string& path) const = 0;
	};
}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月21日：
 * 星翼 删除DeleteFile并加入异常
 * 2016年4月27日：
 * 星翼 删除CopyFile
 */
