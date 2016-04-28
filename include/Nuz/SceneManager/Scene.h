#pragma once
#include <memory>
#include <string>
namespace Nuz{
	class IComponent;
	class IGameObject;

	/* 场景
	* 游戏中一个可以挂载组件和物件和子场景的场面。
	*/
	class IScene{
	public:
	    virtual ~IScene(){};

		/* 挂载组件
		 * 同一个组件多次挂载和单次挂载没什么不同
		 * @param 组件实例
		 */
		virtual void MountComponent(std::shared_ptr<IComponent>) = 0;

		/* 卸载已挂载到该场景的组件
		 * @param name 组件名称
		 */
		virtual void UnmountComponent(const std::string& name) = 0;

		/* 获取已挂载到该场景组件实例
		 * @param name 组件名称
		 * @result 组件实例
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& name) = 0;

		/* 挂载物件
		 * 同一个物件被挂载多次和挂载一次没什么不同。
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
		virtual std::shared_ptr<IComponent> GetMountedGameObject(const std::string& name) = 0;

		/* 挂载一个场景
		 * @param 场景实例
		 */
		virtual void MountScene(std::shared_ptr<IScene>) = 0;

		/* 卸载已挂载的场景
		 * @param name 场景名称
		 */
		virtual void UnmountScene(const std::string& name);

		/* 获取已挂载的场景
		 * @param name 场景名称
		 * @result 场景实例
		 */
		virtual std::shared_ptr<IScene> GetMountedScene(const std::string& name);

		/* 获取场景名称
		 * @result 场景名称
		 */
        virtual std::string GetName() = 0;

		/* 创建场景
         * 创建场景时，名称必须保证唯一，否则弹出异常。
		 * @param name 场景名称
         * @result 场景实例
         */
        static std::shared_ptr<IScene> CreateScene(const std::string& name);
	};
}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给定名称
 */
