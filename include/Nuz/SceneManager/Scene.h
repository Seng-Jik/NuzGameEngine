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
		/* 挂载组件
		 * @param id 组件id
		 * @param 组件实例
		 */
		virtual void MountComponent(const std::string& id,std::shared_ptr<IComponent>) = 0;

		/* 卸载已挂载组件
		 * @param id 组件id
		 */
		virtual void UnmountComponent(const std::string& id) = 0;

		/* 获取已挂载组件实例
		 * @param id 组件id
		 * @result 组件实例
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& id) = 0;

		/* 挂载物件
		 * @param id 物件id
		 * @param 物件实例
		 */
		virtual void MountGameObject(const std::string& id,std::shared_ptr<IGameObject>) = 0;

		/* 卸载已挂载物件
		 * @param id 物件id
		 */
		virtual void UnmountGameObject(const std::string& id);

		/* 获取已挂载物件实例
		 * @param id 物件id
		 * @result 物件实例
		 */
		virtual std::shared_ptr<IComponent> GetMountedGameObject(const std::string& id) = 0;

		/* 挂载一个场景
		 * @param id 场景id
		 * @param 场景实例
		 */
		virtual void MountScene(const std::string& id,std::shared_ptr<IScene>) = 0;

		/* 卸载已挂载的场景
		 * @param id 场景id
		 */
		virtual void UnmountScene(const std::string& id);

		/* 获取已挂载的场景
		 * @param id 场景id
		 * @result 场景实例
		 */
		virtual std::shared_ptr<IScene> GetMountedScene(const std::string& id);
	};
	/* 创建场景
	 * @result 场景实例
	 */
	std::shared_ptr<IScene> CreateScene();
}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 *
 */
