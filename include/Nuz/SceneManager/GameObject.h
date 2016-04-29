#pragma once
#include <memory>
#include <string>
namespace Nuz{
	class IComponent;

	/* 物件
	 * 游戏中一个可以挂载组件的物品。
	 * 下层物件会悬浮在上层物件的上方（2D绘制的状态下）。
	 */
	class IGameObject{
	public:
	    virtual ~IGameObject(){};

		/* 挂载组件
         * 同一个组件多次挂载和单次挂载没什么不同
         * 挂载名在本物件里是唯一的，在全局可以有重名，方便以物件为单位管理组件。
		 * @param 组件实例
		 * @param 挂载名（可以匿名，但你将无法通过挂载名找回它）
		 */
		virtual void MountComponent(const std::shared_ptr<IComponent>&,const std::string& mountName = "") = 0;

		/* 卸载已挂载组件
		 * @param name 组件名称
		 */
		virtual void UnmountComponent(const std::string& name) = 0;

		/* 卸载已挂载组件
		 * @param mountName 组件挂载名
		 */
		virtual void UnmountComponentByMountName(const std::string& mountName) = 0;

		/* 获取已挂载组件实例
		 * @param mountName 组件挂载名
		 * @result 组件实例
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponentByMountName(const std::string& mountName) const = 0;

		/* 挂载物件
		 * @param 物件实例
		 * @param mountName 物件挂载名（可以匿名）
		 */
		virtual void MountGameObject(const std::shared_ptr<IGameObject>&,const std::string& mountName = "") = 0;

		/* 卸载已挂载物件
		 * @param name 物件名称
		 */
		virtual void UnmountGameObject(const std::string& name) = 0;

        /* 卸载已挂载物件
		 * @param name 物件名称
		 */
		virtual void UnmountGameObjectByMountName(const std::string& mountName) = 0;

		/* 获取已挂载物件实例
		 * @param name 物件挂载名
		 * @result 物件实例
		 */
		virtual std::shared_ptr<IGameObject> GetMountedGameObject(const std::string& mountName) const = 0;

		/* 获取物件名称
		 * @result 物件名称
		 */
        virtual std::string GetName() const = 0;

        /* 创建物件
         * 创建物件时，名称必须保证唯一，否则弹出异常。
         * 可以创建匿名物件，匿名物件不可用名称获取。
         * @param name 物件名称
         * @result 物件实例
         */
        static std::shared_ptr<IGameObject> CreateGameObject(const std::string& name = "");

        /* 给定名称获取物件
         * @param name 物件名称
         * @result 物件
         */
        static std::shared_ptr<IGameObject> GetGameObject(const std::string& name);
	};
}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给出名称
 */
