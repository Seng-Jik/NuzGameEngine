#pragma once
#include "Component.h"
#include <memory>

namespace Nuz{
	
	/* 光源
	 * 没有光源时，使用引擎自带的全局光。
	 * 有光源时，引擎不提供光源。
	 */
	class ILight:public IComponent{
	public:
		/* 启动该光源
		 */
		virtual void Enable() = 0;
		
		/* 关闭该光源
		 */
		virtual void Disable() = 0;
		
		/* 设置颜色（光源默认为白色最亮）
		 * @param r 红
		 * @param g 绿
		 * @param b 蓝
		 * @param a Alpha
		 */
		virtual void SetColor(float r,float g,float b,float a) = 0;
		
		/* 设置坐标
		 * @param x x坐标
		 * @param y y坐标
		 * @param z z坐标
		 */
		virtual void SetPos(float x,float y,float z) = 0;
		
		/* 设置为环境光 */
		virtual void SetAmbient() = 0;
		
		/* 设置为漫射光 */
		virtual void SetDiffuse() = 0;
	};
	
	/* 创建一个光源
	 * @result 光源
	 */
	std::shared_ptr<ILight> CreateLight();
}
/* 更新日志：
 * 2016年4月20日：
 * 星翼 初稿
 *
 */
