#pragma once
#include "Component.h"

namespace Nuz{
	class ISprite2D;
	
	/* 2D摄像机
	* 实现2D图像的定位。
	*/
	/* 默认的摄像机
	 * 屏幕中心为(0,0)
	 * 屏幕左上角为(-1,-1)
	 * 屏幕右下角为(1,1)
	 * 以此类推。
	 */
	class ICamera2D:public IComponent{
	public:
		/* 使用此摄像机
		 */
		virtual void Use() = 0;
		
		/* 拍摄照片并返回照片
		 * @result 照片
		 */
		virtual ISprite2D Photograph() = 0;
		
		/* 设置中心坐标
		 * @param x 中心x坐标
		 * @param y 中心y坐标
		 */
		virtual void SetCenter(float x,float y) = 0;
		
		/* 设置从中心到一个边缘的单位大小
		 * @param w 横向大小
		 * @param h 纵向大小
		 */
		virtual void SetZoom(float w,float h) = 0;
		
		/* 以当前摄像机为基准缩放
		 * @param w 横向大小倍数
		 * @param h 纵向大小倍数
		 */
		virtual void Zoom(float w,float h) = 0;
		
		/* 旋转当前摄像机
		 * @param angle 角度
		 * @param x 旋转中心x位置
		 * @param y 旋转中心y位置
		 * @param yFlip 是否绕y轴翻转
		 * @param xFilp 是否绕x轴旋转
		 */
		virtual void Rotate(float angle,float x,float y,bool yFilp,bool xFlip);
		
		/* 以当前摄像机为基准进行平移
		 * @param x 移动的x量
		 * @param y 移动的y量
		 */
		virtual void Move(float x,float y);
	};
	
	/* 创建一个2D摄像机
	 * @result 摄像机
	 */
	std::shared_ptr<ICamera2D> CreateCamera2D();
}
/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 *
 */
