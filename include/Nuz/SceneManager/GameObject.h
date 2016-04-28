#pragma once
#include <memory>
#include <string>
namespace Nuz{
	class IComponent;

	/* 物件
	* 游戏中一个可以挂载组件的物品。
	*/
	class IGameObject{
	public:
	    virtual ~IGameObject(){};

		/* 挂载组件
         * 同一个组件多次挂载和单次挂载没什么不同
		 * @param 组件实例
		 */
		virtual void MountComponent(std::shared_ptr<IComponent>) = 0;

		/* 卸载已挂载组件
		 * @param name 组件名称
		 */
		virtual void UnmountComponent(const std::string& name) = 0;

		/* 获取已挂载组件实例
		 * @param name 组件名称
		 * @result 组件实例
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& name) = 0;

		/* 挂载物件
		 * @param 物件实例
		 */
		virtual void MountGameObject(std::shared_ptr<IGameObject>) = 0;

		/* 卸载已挂载物件
		 * @param name 物件名称
		 */
		virtual void UnmountGameObject(const std::string& name) = 0;

		/* 获取已挂载物件实例
		 * @param name 物件名称
		 * @result 物件实例
		 */
		virtual std::shared_ptr<IGameObject> GetMountedGameObject(const std::string& name) = 0;

		/* 获取物件名称
		 * @result 物件名称
		 */
        virtual std::string GetName() = 0;

        /* 创建物件
         * 创建物件时，名称必须保证唯一，否则弹出异常。
         * @param name 物件名称
         * @result 物件实例
         */
        static std::shared_ptr<IGameObject> CreateGameObject(const std::string& name);

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
