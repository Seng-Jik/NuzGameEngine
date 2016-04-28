#pragma once
#include "../Component.h"
#include <memory>

namespace Nuz{

	/* 雾气
	*/
	class IFog3D:public IComponent{
	public:
		/* 使用颜色（默认白色）
		* @param r 红
		* @param g 绿
		* @param b 蓝
		*/
		virtual void SetColor(float r,float g,float b) = 0;

		/* 添加体积雾参数（设置此参数后则设置为体积雾，至少要有三个绑定才能变成体积雾）
		 * @param x x坐标
		 * @param y y坐标
		 * @param z z坐标
		 * @param f 雾强度
		 */
		virtual void SetFogWalls(
			float x,
			float y,
			float z,
			float f
		) = 0;

		/* 设置为全局雾（默认，会丢失已绑定的体积雾参数）
		*/
		virtual void SetGlobal() = 0;

        /* 创建一个雾气组件
         * @param name 组件名
         * @result 雾气组件
         */
        static std::shared_ptr<IFog3D> CreateFog3D(const std::string& name);
	};
}
/* 更新日志：
 * 2016年4月20日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 移动创建方法并给定名称
 */
