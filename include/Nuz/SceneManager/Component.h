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
	public:
	    /* 构造时注意事项
	     * 你必须保证每个组件都有一个唯一的组件名称
	     * 当名称冲突时将会弹出异常
	     * @param name 组件名称
	     */
	    IComponent(const std::string& name);
	    virtual ~IComponent(){};

		virtual void OnInit(){};	//当初始化组件被引擎开始使用时
		virtual void OnQuit(){};	//当该组件不再被引擎使用时
		virtual void OnShow(){};	//当物件开始被显示时执行
		virtual void OnHide(){};	//当物件被隐藏时执行
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

		/* 取得组件名称
		 * @result 组件名
		 */
        virtual std::string GetName() = 0;

        /* 给定名称返回组件
         * @param name 组件名
         * @result 组件
         */
        static std::shared_ptr<IComponent> GetComponent(const std::string name);

        /* 父节点类型 */
		enum class ParentType{
		    None,   //没有被挂载
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
	};

}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给出组件名称
 */
