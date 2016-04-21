#pragma once
#include <memory>

namespace Nuz{
	class ISceneManager;
	class IFileSystem;
	class IInputDeviceManager;
	
	/* Nuz引擎主体部分
	 * 包含了Nuz引擎类
	 */
	class IEngine{
	public:
		virtual ISceneManager& GetSceneManager() = 0;
		virtual IFileSystem& GetFileSystem() = 0;
		virtual IInputDeviceManager& GetInputDeviceManager() = 0;
		virtual ILocalFile& GetLocalFile() = 0;
	};
	
	/* 创建引擎实例
	 * @result 指向引擎的指针
	 */
	std::shared_ptr<IEngine> CreateGameDevice();
}

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 * 2016年4月18日：
 * 星翼 修正CreateGameDevice函数的返回值并加上说明。
 * 星翼 添加GetLocalFile方法。
 */
