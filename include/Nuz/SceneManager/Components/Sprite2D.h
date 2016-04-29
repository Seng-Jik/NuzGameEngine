#pragma once
#include "../Component.h"
#include <memory>
#include <string>

namespace Nuz{

	/* 2D精灵组件
	* 实现2D图像的绘制。
	*/
	class ISprite2D:public IComponent{
	public:
		/* 使用图像
		* @param path 图像文件
		* @param num 图像编号
		*/
		virtual void UseImage(const std::string& path,int num = 0) = 0;

		/* 使用文本
		 * @param fontPath 字体路径
		 * @param text 文本
		 * @param size 字体大小
		 */
		virtual void UseText(const std::string& fontPath,const std::wstring& text,int size) = 0;

		/* 释放图像
		*/
		virtual void FreeImage() = 0;

		/* 设置只使用一块子图像
		* @param x 图像左上角x位置（-1~1）
		* @param y 图像左上角y位置(-1~1)
		* @param w 图像的宽
		* @param h 图像的高
		*/
		virtual void SetSrc(float x,float y,int w,int h) = 0;

		/* 设置只使用一块子图像
		* @param x 图像左上角x位置（像素）
		* @param y 图像左上角y位置(像素)
		* @param w 图像的宽
		* @param h 图像的高
		*/
		virtual void SetSrc(int x,int y,int w,int h) = 0;

		/* 获取当前图像总大小
		* @param w 宽
		* @param h 高
		*/
		virtual void GetSize(int& w,int& h) const = 0;

		/* 设置图像绘制的目的中心位置
		* @param x 当前摄像机x位置
		* @param y 当前摄像机y位置
		*/
		virtual void SetPos(float x,float y) = 0;

		/* 设置目标位置的大小
		* @param w 宽度（比率）
		* @param h 高度（比率）
		*/
		virtual void SetDstSize(float w,float h) = 0;

		/* 设置旋转
		 * @param x 旋转中心x
		 * @param y 旋转中心y
		 * @param angle 旋转角度
		 * @param yFlip 是否绕y轴旋转
		 * @param xFlip 是否绕x轴旋转
		 */
		virtual void SetRotate(float x,float y,float angle,bool yFlip,bool xFlip) = 0;

        /* 创建一个2D精灵组件
         * @param name 组件名称
         * @result 精灵组件
         */
        static std::shared_ptr<ISprite2D> CreateSprite2D(const std::string& name ="");
	};
}
/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给定名称
 */
