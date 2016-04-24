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
     * @throw CannotCreateEngine
	 * @result 引擎
	 */
	IEngine& CreateGameDevice(const char* title,bool fullScreen,int w=-1,int h=-1);

	/* 取得已被创建的引擎实例
     * @throw HaveNotEngine
     * @result 引擎
     */
	IEngine& GetGameDevice();

	/* 销毁引擎实例
	 * @throw HaveNotEngine
	 */
    void KillGameDevice();

    /* 异常类：无法创建引擎 */
    class CannotCreateEngine:public std::runtime_error{
    public:
        inline CannotCreateEngine(const std::string& s):std::runtime_error(s){};
    };

    /* 异常类：没有创建引擎 */
    class HaveNotEngine:public std::runtime_error{
    public:
        inline HaveNotEngine(const std::string& s):std::runtime_error(s){};
    };
}

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 * 2016年4月18日：
 * 星翼 修正CreateGameDevice函数的返回值并加上说明。
 * 星翼 添加GetLocalFile方法。
 * 2016年4月24日：
 * 星翼 添加引擎生命异常。
 */
