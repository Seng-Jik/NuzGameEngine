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
		    None,   //没有被挂载
			TypeScene,	//场景
			TypeGameObject	//游戏物件
		};

		/* 获取父节点类型
		 * @result 父节点类型
		 */
		virtual ParentType GetParentType() = 0;

        /* 获取作为场景的父节点实例
		 * @result 父节点
		 */
		virtual std::shared_ptr<IScene> GetSceneParent() = 0;

        /* 获取作为物件的父节点实例
		 * @result 父节点
		 */
		virtual std::shared_ptr<IGameObject> GetGameObjectParent() = 0;

		/* 给定挂载名，取父节点中对应挂载名的组件
		 * @param 挂载名
		 */
        virtual std::shared_ptr<IComponent> GetOtherComponent(const std::string& mountName) = 0;

        /* 给定挂载名，取父节点中对应挂载名的物件
		 * @param 挂载名
		 */
        virtual std::shared_ptr<IGameObject> GetGameObjectByMountName(const std::string& mountName) = 0;

        /* 获取该组件所在的场景
         * @result 场景名称
         */
        virtual std::string GetSceneName() = 0;
	public:
	    /* 构造时注意事项
	     * 你必须保证每个组件都有一个唯一的组件名称
         * 当名称为空时则为匿名，匿名组件不可用名称获取。
	     * 当名称冲突时将会弹出异常
	     * @param name 组件名称
	     */
	    IComponent(const std::string& name = "");
	    virtual ~IComponent(){};

		virtual void OnInit(){};	//当初始化组件被引擎开始使用时
		virtual void OnQuit(){};	//当该组件不再被引擎使用时
		virtual void OnShow(){};	//当物件开始被显示时执行
		virtual void OnHide(){};	//当物件被隐藏时执行
		virtual void OnUpdate(){};	//当组件需要更新逻辑时执行

		virtual void OnDraw3DReady(){};	//当准备绘制3D时执行
		virtual void OnDraw3D(){};	//当组件需要绘制3D时执行
		virtual void OnDraw3DFinished(){};	//当3D绘制完成后

        virtual void OnDraw2DReady(){};	//当准备绘制2D物件时执行
		virtual void OnDraw2D(){};	//当组件需要绘制2D物件时执行
		virtual void OnDraw2DFinished(){};	//当2D物件绘制完成后

        virtual void OnDrawSceneReady(){};    //当场景绘制准备开始时
		virtual void OnDrawScene(){}; //当绘制场景时
		virtual void OnDrawSceneFinished(){}; //当场景绘制结束时
		/* 绘制流程
		 * 如果被挂载的是2D或3D物件，则会只调用物件绘制函数，不调用Scene绘制函数。
		 * 如果被挂载的是场景，则先作为一个物件进行绘制，然后把该场景绘制得到的图像作为帧缓存，再次调用场景绘制函数。
		 */

		/* 当场景要求被切出时执行
		 * @param timeLimited 时间限制（帧）
		 */
		virtual void OnFadeSwitchOut(int timeLimited){};

		/* 当场景被切出时会增加的增补逻辑
		 * @param finished 时间剩余百分比
		 */
		virtual void OnFadeSwitchOutUpdate(float finished){};

		/* 当场景要求被切入时执行
		 * @param timeLimited 时间限制（帧）
		 */
		virtual void OnFadeSwitchIn(int timeLimited){};

		/* 当场景被切入时会增加的增补逻辑
		 * @param finished 时间剩余百分比
		 */
		virtual void OnFadeSwitchInUpdate(float finished){};

		/* 取得组件名称
		 * @result 组件名
		 */
        virtual std::string GetName() const = 0;

        /* 给定名称返回组件
         * @param name 组件名
         * @result 组件
         */
        static std::shared_ptr<IComponent> GetComponent(const std::string name);
	};

}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给出组件名称
 */
