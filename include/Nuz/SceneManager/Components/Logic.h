#pragma once
#include "Component.h"

namespace Nuz{
	
	/* 逻辑组件
	 * 实现逻辑
	 */
	class ILogic:public IComponent{
	public:
		virtual void OnInit(){};	//当初始化组件时执行
		virtual void OnQuit(){};	//当该组件不再使用时执行
		virtual void OnShow(){};	//当组件开始被显示时执行
		virtual void OnHide(){};	//当组件被隐藏时执行
		virtual void OnUpdate(){};	//当组件需要更新逻辑时执行
		
		/* 当场景要求被切出时执行
		 * @param 时间限制（帧）
		 */
		virtual void OnFadeSwitchOut(int timeLimited){};
		
		/* 当场景被切出时会增加的增补逻辑
		 * @param 时间剩余百分比
		 */
		virtual void OnFadeSwitchOutUpdate(float finished){};
		
		/* 当场景要求被切入时执行
		 * @param 时间限制（帧）
		 */
		virtual void OnFadeSwitchIn(int timeLimited){};
		
		/* 当场景被切入时会增加的增补逻辑
		 * @param 时间剩余百分比
		 */
		virtual void OnFadeSwitchInUpdate(float finished){};
	};
}
/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 *
 */
