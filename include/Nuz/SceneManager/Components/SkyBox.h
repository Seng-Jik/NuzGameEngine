#pragma once
#include "../Component.h"
#include <memory>
#include <string>
#include "Camera3D.h"

namespace Nuz{

	/* 天空盒组件
	* 实现3D天空效果。
	*/
	class ISkyBox:public IComponent{
	public:
		/* 使用图像
         * @param path 图像文件
         * @param num 图像编号
         * @param where 编号（0-顶，1-底，2-前，3-后，4-左，5-右，-1-全部，-2-四方）
		 */
		virtual void UseImage(const std::string& path,int num = 0,int where = -1) = 0;

		/* 设置跟随目标
         * @param ICamera3D对象
         */
		virtual void SetCamera3D(const std::shared_ptr<ICamera3D>) = 0;

		/* 释放图像
         * @param where 编号（0-顶，1-底，2-前，3-后，4-左，5-右，-1-全部，-2-四方）
         */
		virtual void FreeImage(int where = -1) = 0;

        /* 创建一个天空盒
         * @param name 组件名称
         * @result 天空盒
         */
        static std::shared_ptr<ISkyBox> CreateSkyBox(const std::string& name);
	};
}
/* 更新日志：
 * 2016年4月27日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给定名称
 */
