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

	    /* 初始化游戏窗口
	     * @param w 宽度（如果全屏时采用屏幕分辨率，填入-1）
	     * @param h 高度（如果全屏时采用屏幕分辨率，填入-1）
	     * @param fullScreen 是否全屏
	     */
        virtual void InitWindow(int w,int h,bool fullScreen) = 0;

        /* 设置游戏窗口标题
         * @param title 标题
         */
        virtual void SetWindowTitle(const std::string& title) noexcept = 0;

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

	/* 取得已被创建的引擎实例
     * @throw HaveNotEngine
     * @result 引擎
     */
	IEngine& GetGameDevice() noexcept;

}

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 * 2016年4月18日：
 * 星翼 修正CreateGameDevice函数的返回值并加上说明。
 * 星翼 添加GetLocalFile方法。
 * 2016年4月24日：
 * 星翼 添加引擎生命异常。
 * 2016年4月26日：
 * 星翼 修改引擎生命周期
 */
