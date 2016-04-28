#pragma once
#include "../Component.h"

namespace Nuz{

	/* 逻辑组件
	 * 实现逻辑
	 */
	class ILogic:public IComponent{
	public:
	    /* 构造时注意
	     * 给定一个组件名称，详见../IComponent.h
	     * @param name 组件名称
	     */
	    using IComponent::IComponent;
		void OnInit() override{};	//当初始化组件时执行
        void OnQuit() override{};	//当该组件不再使用时执行
        void OnShow() override{};	//当组件开始被显示时执行
        void OnHide() override{};	//当组件被隐藏时执行
        void OnUpdate() override{};	//当组件需要更新逻辑时执行

		/* 当场景要求被切出时执行
		 * @param 时间限制（帧）
		 */
        void OnFadeSwitchOut(int timeLimited) override{};

		/* 当场景被切出时会增加的增补逻辑
		 * @param 时间剩余百分比
		 */
        void OnFadeSwitchOutUpdate(float finished) override{};

		/* 当场景要求被切入时执行
		 * @param 时间限制（帧）
		 */
        void OnFadeSwitchIn(int timeLimited) override{};

		/* 当场景被切入时会增加的增补逻辑
		 * @param 时间剩余百分比
		 */
        void OnFadeSwitchInUpdate(float finished) override{};
	};
}
/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月27日：
 * 星翼 修改为override方式
 * 2016年4月28日：
 * 星翼 给定名称
 */
