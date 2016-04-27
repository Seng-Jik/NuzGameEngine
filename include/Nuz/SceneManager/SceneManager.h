#pragma once
#include <cstdint>
namespace Nuz{
	class IScene;
	/* Nuz场景管理器
	* 推动整个游戏的运作。
	*/
	class ISceneManager{
	public:
		/* 运行一个场景，只允许在启动游戏时调用它。
		 * @param 你要启动的场景
		 */
		virtual void Start(IScene&) = 0;

		/* 平滑切换到一个场景，有切换特效。
		 * 切换特效由场景提供。
		 * @param 要跳转到的场景
		 * @param time 动画切换时间
		 */
		virtual void FadeTo(IScene&,uint32_t time) = 0;

		/* 请求退出场景，并把Start()跳出。
		 */
		virtual void Exit() = 0;
	};
}

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 *
 */
