#pragma once
#include <memory>

namespace Nuz{
	class ISceneManager;
	class IFileSystem;
	class IInputDeviceManager;
	class ILocalFile;

	/* Nuz引擎主体部分
	 * 包含了Nuz引擎类
	 */
	class IEngine{
	public:

	    /* 取得场景管理器
	     * @result 场景管理器
	     */
		virtual ISceneManager& GetSceneManager() = 0;

		/* 取得文件系统
		 * @result 文件系统
		 */
		virtual IFileSystem& GetFileSystem() = 0;

		/* 取得输入管理器
		 * @result 输入管理器
		 */
		virtual IInputDeviceManager& GetInputDeviceManager() = 0;

		/* 取得本地文件管理器
		 * @result 本地文件管理器
		 */
		virtual ILocalFile& GetLocalFile() = 0;
	};

	/* 创建引擎实例
	 * @param fullScreen 是否全屏
	 * @param w 宽度（为-1则在全屏模式下按照屏幕分辨率设定）
     * @param h 高度（为-1则在全屏模式下按照屏幕分辨率设定）
     * @param title 标题
	 * @result 指向引擎的指针
	 */
	std::shared_ptr<IEngine> CreateGameDevice(const char* title,bool fullScreen,int w=-1,int h=-1);
}

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 * 2016年4月18日：
 * 星翼 修正CreateGameDevice函数的返回值并加上说明。
 * 星翼 添加GetLocalFile方法。
 */
