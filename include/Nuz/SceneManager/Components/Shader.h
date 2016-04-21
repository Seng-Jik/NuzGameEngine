#pragma once
#include <memory>
#include <string>
#include "../Component.h"

namespace Nuz{

	/* 着色器
	 */
	class IShader:public IComponent{
	public:

		/* 启动该着色器
		 */
		virtual void Use() = 0;

		/* 停用该着色器
		 */
		virtual void Unuse() = 0;

	};
	/* 创建着色器并返回着色器实例
	 * @param vert 顶点着色器文件名
	 * @param frag 片元着色器文件名
	 * @result 着色器实例
	 */
	std::shared_ptr<IShader> CreateShader(const std::string& vert,const std::string& frag);
}
/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 *
 */
