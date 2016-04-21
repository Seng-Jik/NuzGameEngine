#pragma once
#include <memory>

namespace Nuz{
	class IKeyboard;

	/* 此处不属于最小Nuz范围 */
	#ifdef NUZ_VER_FULL
	class IGamePad;
	#endif

	/* 输入设备管理器
	 * 负责管理所有的输入设备
	 */
	class IInputDevieManager{
	public:

		/* 获取键盘控制器
		 * @result 键盘控制器指针（当键盘不存在时为nullptr）
		 */
		virtual std::shared_ptr<IKeyboard> GetKeyboard() = 0;

		/* 此处不属于最小Nuz范围 */
		#ifdef NUZ_VER_FULL

		/* 获取接入手柄数量
		 * @result 手柄数量
		 */
		virtual int GetGamePadNum() = 0;

		/* 获取接入手柄
		 * @param 手柄编号
		 * @result 手柄实例
		 */
		 virtual std::shared_ptr<IGamePad> GetGamePad(int) = 0;
		#endif
	};
}

/* 更新日志：
 * 2016年4月17日：
 * 星翼 初稿
 *
 */
