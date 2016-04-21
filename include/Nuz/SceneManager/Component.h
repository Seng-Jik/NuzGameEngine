#pragma once
#include <memory>

namespace Nuz{
	class IScene;
	class IGameObject;
	
	/* 组件
	* 依赖在物件或场景上的一组逻辑和功能。
	*/
	class IComponent{
	protected:
		/* 父节点类型 */
		enum class ParentType{
			TypeScene,	//场景
			TypeGameObject	//游戏物件
		};
		
		/* 获取父节点类型
		 * @result 父节点类型
		 */
		virtual ParentType GetParentType() = 0;
		
		/* 获取作为物件的父节点
		 * @result 父节点实例
		 */
		virtual std::shared_ptr<IGameObject> GetParentGameObject() = 0;
		
		/* 获取作为场景的父节点
		 * @result 父节点实例
		 */
		virtual std::shared_ptr<IScene> GetParentScene() = 0;
	public:
		virtual void OnInit(){};	//当初始化组件时执行
		virtual void OnQuit(){};	//当该组件不再使用时执行
		virtual void OnShow(){};	//当组件开始被显示时执行
		virtual void OnHide(){};	//当组件被隐藏时执行
		virtual void OnUpdate(){};	//当组件需要更新逻辑时执行
		
		virtual void OnDraw2DReady(){};	//当准备绘制2D时执行
		virtual void OnDraw2D(){};	//当组件需要绘制2D时执行
		virtual void OnDraw2DFinished(){};	//当2D绘制完成后
		
		virtual void OnDraw3DReady(){};	//当准备绘制3D时执行
		virtual void OnDraw3D(){};	//当组件需要绘制3D时执行
		virtual void OnDraw3DFinished(){};	//当3D绘制完成后
		
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
