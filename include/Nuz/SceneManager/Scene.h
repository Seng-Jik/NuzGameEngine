#pragma once
#include <memory>
#include <string>
#include "Camera2D.h"
#include "Camera3D.h"

namespace Nuz{
	class IComponent;
	class IGameObject;

	/* 场景
	 * 游戏中一个可以挂载组件和物件和子场景的场面。
     * 上层场景会悬浮在下层场景的上方。
     * 场景会被转换为2D图像进行覆盖显示。
	 */
	class IScene{
	public:
	    virtual ~IScene(){};

		/* 挂载组件
		 * 同一个组件多次挂载和单次挂载没什么不同
		 * @param 组件实例
		 * @param mountName 挂载名，可以匿名
		 */
		virtual void MountComponent(const std::shared_ptr<IComponent>&,const std::string mountName = "") = 0;

		/* 卸载已挂载到该场景的组件
		 * @param name 组件名称
		 */
		virtual void UnmountComponent(const std::string& name) = 0;

        /* 卸载已挂载到该场景的组件
		 * @param mountName 组件名称
		 */
		virtual void UnmountComponentByMountName(const std::string& mountName) = 0;

		/* 获取已挂载到该场景组件实例
		 * @param mountName 挂载名
		 * @result 组件实例
		 */
		virtual std::shared_ptr<IComponent> GetMountedComponent(const std::string& mountName) const = 0;

		/* 挂载物件
		 * 同一个物件被挂载多次和挂载一次没什么不同。
		 * @param 物件实例
		 * @param mountName 挂载名（可以匿名）
		 */
		virtual void MountGameObject(const std::shared_ptr<IGameObject>&,const std::string& mountName = "") = 0;

		/* 卸载已挂载物件
		 * @param name 物件名称
		 */
		virtual void UnmountGameObject(const std::string& name) = 0;

        /* 卸载已挂载物件
		 * @param mountNameame 物件挂载名
		 */
		virtual void UnmountGameObjectByMountName(const std::string& mountName) = 0;

		/* 获取已挂载物件实例
		 * @param mountName 物件挂载名
		 * @result 物件实例
		 */
		virtual std::shared_ptr<IGameObject> GetMountedGameObject(const std::string& mountName) const = 0;

		/* 挂载一个场景
		 * @param 场景实例
		 */
		virtual void MountScene(const std::shared_ptr<IScene>&) = 0;

		/* 卸载已挂载的场景
		 * @param name 场景名称
		 */
		virtual void UnmountScene(const std::string& name);

		/* 设置摄像机
		 * 2D/3D摄像机均可各设置一个。
		 * @param camera 摄像机
		 */
        virtual void SetCamera2D(const std::shared_ptr<const ICamera2D>& camera) = 0;
        virtual void SetCamera3D(const std::shared_ptr<const ICamera3D>& camera) = 0;

		/* 获取场景名称
		 * @result 场景名称
		 */
        virtual std::string GetName() const = 0;

		/* 创建场景
         * 创建场景时，名称必须保证唯一，否则弹出异常。
		 * @param name 场景名称
         * @result 场景实例
         */
        static std::shared_ptr<IScene> CreateScene(const std::string& name);

        /* 通过名称获取场景
         * @param name 场景名称
         * @result 场景
         */
        static std::shared_ptr<IScene> GetScene(const std::string& name);
	};
}

/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给定名称
 */
