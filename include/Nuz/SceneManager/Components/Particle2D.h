#pragma once
#include "../Component.h"
#include <string>
#include <functional>

namespace Nuz{

	/* 单个粒子 */
	/* 注意：没有错误检查。
	 * 你必须挂载全局粒子处理器、单个粒子处理器以及一个点纹理。
	 * 你可以手动检查粒子系统是否可以使用。
	 */
	class IDot2D{
	public:
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
		virtual float GetSpeed() const = 0;

		/* 设置透明度，Alpha小于等于0时自动杀掉该粒子。
		 * @param a 透明度
		 */
		virtual void SetAlpha(float a) = 0;

		/* 当前基础上增加透明度，Alpha小于等于0时自动杀掉该粒子。
		 * @param a 透明度
		 */
		virtual void AddAlpha(float a) = 0;

		/* 获取透明度
		 * @result 透明度
		 */
		virtual float GetAlpha() const = 0;

		/* 获取当前角度
		 * @result 角度
		 */
		virtual float GetAngle() const = 0;

		/* 设置角度
		 * @param a 角度
		 */
		virtual void SetAngle(float a) = 0;

		/* 在当前基础上增加角度
		 * @param 角度
		 */
		virtual void AddAngle(float a) = 0;

		/* 设置状态（n的范围：0~3）
		 * 用于用户自定义
		 * @param n 要指定的状态号
		 * @param status 状态
		 */
		virtual void SetStatus(int n,float status) = 0;

		/* 获取状态（n的范围：0~3）
		 * 用于用户自定义
		 * @param n 状态号
		 * @result 状态
		 */
		virtual float GetStatus(int n) const = 0;

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
		virtual void GetRGB(float& r,float& g,float& b) const = 0;

		/* 在当前基础上增加过滤量
		 * @param r 红(加和在0~1之间)
		 * @param g 绿(加和在0~1之间)
		 * @param b 蓝(加和在0~1之间)
		 */
		virtual void AddRGB(float r,float g,float b) = 0;

		/* 获取粒子坐标
		 * @param x x位置
		 * @param y y位置
		 */
		virtual void GetPos(float& x,float& y) const = 0;

        /* 设置大小
		 * @param 大小（1为普通大小，0自动杀除粒子）
		 */
        virtual void SetSize(float) = 0;

        /* 获取大小
         * @result 大小
         */
        virtual float GetSize() const = 0;

        /* 在已有基础上增加大小（1为普通大小，0自动杀除粒子）
         * @param 增量
         */
        virtual void AddSize(float) = 0;

		/* 取得生命时长（帧）
		 * @result 帧数
		 */
		virtual uint32_t GetLife() const = 0;
	};

	/* 2D粒子组件 */
	class IParticle2D:public Nuz::IComponent{
	public:
		/* 使用一个粒子纹理
		* @param 文件
		* @param 图像编号
		*/
		virtual void UseImage(const std::string&,int = 0) = 0;

		/* 绑定单个粒子处理器
		 * 粒子处理器每帧都会遍历每个粒子
		 * 你可以处理这些粒子的行为
		 * @param 要绑定的粒子处理器
		*/
		virtual void BindSingle(std::function<void(IParticle2D&,IDot2D&)>) = 0;

		/* 添加粒子
		 * @param x 粒子初始x坐标
		 * @param y 粒子初始y坐标
		 * @param num 粒子数量
		 * 该粒子会立刻被粒子处理器处理
		 */
		virtual void AddDot(float x,float y,int num) = 0;

		/* 检查粒子系统是否正确 
		 * 如果不可用则弹出std::runtime_error
		 * @throw std::runtime_error
		 */
		virtual void Check() = 0;

		/* 粒子是否为空
		 * @result 是否为空
		 */
		virtual bool Empty() = 0;

		/* 删除所有粒子
		 */
		virtual void Clear() = 0;

        /* 创建2D粒子系统
         * @result 2D粒子系统
         */
        static std::shared_ptr<IParticle2D> CreateParticle2D();
	};
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 * 2016年4月28日：
 * 星翼 给定名称
 */
