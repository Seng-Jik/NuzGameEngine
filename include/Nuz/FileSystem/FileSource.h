#pragma once
#include <memory>
#include <string>
#include <vector>
namespace Nuz{
	/* 文件数据源
		完成该类后可以挂载到虚拟文件系统上。
	 */
	class IFileSource{
	public:
	    virtual ~IFileSource(){};

		/* 读取文件
		 * 提供一个开头为/的文件路径
		 * 从这里读取文件并返回。
		 * 如果没有这个文件，请返回nullptr，可以不用设置size
		 * @param path 文件路径
		 * @throw CannotOpenFile 如果无法加载文件，请弹出该异常
		 * @result 返回给引擎的文件缓存区，如果加载失败请返回nullptr.
		 */
		virtual std::shared_ptr<std::vector<uint8_t> > ReadFile(const std::string& path) const = 0;
	};
}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月21日：
 * 加入异常
 */
