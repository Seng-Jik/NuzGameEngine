#pragma once
#include <memory>

namespace Nuz{
	class IJoystick;
	
	/* 手柄控制器 */
	class IGamePad{
	public:
		/* 取得按键数量
		 * @result 按键数量
		 */
		virtual int GetButtonNums() = 0;
		
		/* 取得按键是否已经按下
		 * @param n 按键编号
		 * @result 按键是否已经按下
		 */
		virtual bool KeyPressed(int n) = 0;
		
		/* 取得手柄的摇杆或十字键数量
		 * @result 数量
		 */
		virtual int GetJoystickNum() = 0;
		
		/* 取得第n个摇杆或十字键
		 * @param n 摇杆或十字键编号
		 * @result 摇杆或十字键实例
		 */
		virtual std::shared_ptr<IJoystick> GetJoystick() = 0;
	};
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 *
 */
