#pragma once
#include "../Component.h"
#include <string>
#include <functional>
#include <memory>

namespace Nuz{

	/* 单个粒子 */
	class IDot3D{
	public:
		/* 使用一个粒子纹理
		 * @param 文件
		 */
		virtual void UseImage(const std::string&) = 0;

		/* 不使用粒子纹理
		 * 使用一个白色的点代替
		 */
		virtual void UnuseImage() = 0;

		/* 设置速度
		 * @param s 速度
		 */
		virtual void SetSpeed(float s) = 0;

		/* 在当前基础上增加速度
		 * @param s 速度
		 */
		virtual void AddSpeed(float s) = 0;

		/* 取得速度
		 * @result 速度
		 */
		virtual float GetSpeed() = 0;

		/* 设置透明度
		 * @param a 透明度
		 */
		virtual void SetAlpha(float a) = 0;

		/* 当前基础上增加透明度
		 * @param a 透明度
		 */
		virtual void AddAlpha(float a) = 0;

		/* 获取透明度
		 * @result 透明度
		 */
		virtual float GetAlpha() = 0;

		/* 获取当前角度
		 * 这里使用一个三维向量表示
		 * @param a 向量x分量
		 * @param b 向量y分量
		 * @param c 向量z分量
		 */
		virtual void GetAngle(float& a,float& b,float& c) = 0;

		/* 设置角度
		 * 这里使用一个三维向量表示
		 * @param a 向量x分量
		 * @param b 向量y分量
		 * @param c 向量z分量
		 */
		virtual void SetAngle(float a,float b,float c) = 0;

		/* 在当前基础上增加角度
		 * 这里使用一个三维向量表示
		 * @param a 向量x分量
		 * @param b 向量y分量
		 * @param c 向量z分量
		 */
		virtual void AddAngle(float a,float b,float c) = 0;

		/* 设置状态
		 * 用于用户自定义
		 * @param n 要指定的状态号
		 * @param status 状态
		 */
		virtual void SetStatus(int n,float status) = 0;

		/* 获取状态
		 * 用于用户自定义
		 * @param n 状态号
		 * @result 状态
		 */
		virtual float GetStatus(int n) = 0;

		/* 设置粒子颜色过滤
		 * @param r 红(0~1)
		 * @param g 绿(0~1)
		 * @param b 蓝(0~1)
		 */
		virtual void SetRGB(float r,float g,float b) = 0;

		/* 取得粒子颜色过滤
		 * @param r 红(0~1)
		 * @param g 绿(0~1)
		 * @param b 蓝(0~1)
		 */
		virtual void GetRGB(float& r,float& g,float& b) = 0;

		/* 在当前基础上增加过滤量
		 * @param r 红(加和在0~1之间)
		 * @param g 绿(加和在0~1之间)
		 * @param b 蓝(加和在0~1之间)
		 */
		virtual void AddRGB(float r,float g,float b) = 0;

		/* 获取粒子坐标
		 * @param x x位置
		 * @param y y位置
		 * @param z z位置
		 */
		virtual void GetPos(float& x,float& y,float& z) = 0;

		/* 取得生命时长（帧）
		 * @result 帧数
		 */
		virtual uint32_t GetLife() = 0;

		/* 杀掉此粒子
		 */
		virtual void Kill() = 0;
	};

	/* 2D粒子组件 */
	class IParticle3D{
	public:

		/* 绑定粒子处理器
		 * 粒子处理器每帧都会遍历每个粒子
		 * 你可以处理这些粒子的行为
		 * @param 要绑定的粒子处理器
		*/
		virtual void BindFunction(std::function<void(IParticle3D&,IDot3D&)>) = 0;

		/* 添加粒子
		 * 该粒子会立刻被粒子处理器处理
		 */
		virtual void AddDot() = 0;
	};

	/* 创建3D粒子系统
	 * @result 3D粒子系统
	 */
	std::shared_ptr<IParticle3D> CreateParticle3D();
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 *
 */
