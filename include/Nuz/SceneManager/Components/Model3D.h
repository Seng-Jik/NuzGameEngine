#pragma once
#include "../Component.h"
#include <memory>
#include <string>

namespace Nuz{

	/* 3D模型组件
	* 实现2D图像的绘制。
	*/
	class IModel3D:public IComponent{
	public:
		/* 使用模型
		 * @param 3D模型路径
		 */
		virtual void UseModel(const std::string&) = 0;

		/* 使用2D图像（生成一个3D空间的四边形）
		* @param path 图像文件
		* @param num 图像编号
		*/
		virtual void UseImage2D(const std::string& path,int num = 0) = 0;

		/* 使用文本（生成一个3D空间的四边形）
		 * @param fontPath 字体路径
		 * @param text 文本
		 * @param size 字体大小
		 */
		virtual void UseText2D(const std::string& fontPath,const std::wstring& text,int size) = 0;

		/* 释放模型
		*/
		virtual void FreeModel() = 0;

		/* 设置模型的坐标位置
		 * @param x x位置
		 * @param y y位置
		 * @param z z位置
		 */
		virtual void SetPos(float x,float y) = 0;

		/* 设置是否显示
		 * @param 是否显示
		 */
		virtual void SetVisible(bool) = 0;

		/* 设置旋转
		 * @param x 旋转中心x
		 * @param y 旋转中心y
		 * @param angle 旋转角度
		 * @param yFlip 是否绕y轴旋转
		 * @param xFlip 是否绕x轴旋转
		 */
		virtual void SetRotate(float x,float y,float angle,bool yFlip,bool xFlip) = 0;

		/* 设置缩放
		 * @param x x方向缩放
		 * @param y y方向缩放
		 * @param z z方向缩放
		 */
		virtual void SetZoom(float x,float y,float z) = 0;

		/* 在当前基础上缩放
		 * @param x x方向缩放
		 * @param y y方向缩放
		 * @param z z方向缩放
		 */
		 virtual void Zoom(float x,float y,float z) = 0;

        /* 创建一个3D模型组件
         * @param name 组件名称
         * @result 模型组件
         */
        static std::shared_ptr<IModel3D> CreateModel3D(const std::string& name);
	};
}
/* 更新日志：
 * 2016年4月20日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给定名称
 */
