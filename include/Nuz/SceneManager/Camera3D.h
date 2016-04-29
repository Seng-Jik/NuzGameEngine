#pragma once

namespace Nuz{

	/* 3D摄像机
	* 实现3D图像拍摄的定位。
	*/
	/* 默认的摄像机
	 * 45度视角
	 * 屏幕中心为(0,0)
	 * 屏幕左上角为(-1,-1)
	 * 屏幕右下角为(1,1)
	 * 从无限远到无限近为(-1~1)
	 * 以此类推。
	 */
	class ICamera3D{
	public:

		/* 设置中心坐标
		 * @param x 中心x坐标
		 * @param y 中心y坐标
		 * @param z 中心z坐标
		 */
		virtual void SetCenter(float x,float y,float z) = 0;

		/* 设置从中心到一个边缘的单位大小
		 * @param w 横向大小
		 * @param h 纵向大小
		 * @param d 无限远到无限近大小
		 */
		virtual void SetZoom(float w,float h,float d) = 0;

		/* 以当前摄像机为基准缩放
		 * @param w 横向大小倍数
		 * @param h 纵向大小倍数
		 * @param d 无限远到无限近大小倍数
		 */
		virtual void Zoom(float w,float h,float d) = 0;

		/* 旋转当前摄像机
		 * @param angle 角度
		 * @param x 旋转轴向量x分量
		 * @param y 旋转轴向量y分量
		 * @param z 旋转轴向量z分量
		 */
		virtual void Rotate(float angle,float x,float y,float z);

		/* 以当前摄像机为基准进行平移
		 * @param x 移动的x量
		 * @param y 移动的y量
		 * @param z 移动的z量
		 */
		virtual void Move(float x,float y,float z);

		/* 设置摄像机视野角度
		 * @param 角度
		 */
		virtual void SetFov(float) = 0;

        /* 创建一个3D摄像机
         * @result 摄像机
         */
        static std::shared_ptr<ICamera3D> CreateCamera3D();
	};
}
/* 更新日志：
 * 2016年4月18日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 移动创建方法并给定名称
 * 星翼 不再是组件
 */
