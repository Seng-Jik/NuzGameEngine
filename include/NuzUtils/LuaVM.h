#pragma once
#include <memory>
#include <string>

namespace NuzUtils{

	/* Lua虚拟机
	 */
	class ILuaVM{
	public:
	
		/* 载入Lua标准库 */
		virtual void OpenLibMath() = 0;	//数学
		virtual void OpenLibIO() = 0;	//IO
		virtual void OpenLibString() = 0;	//字符串
		virtual void OpenLibTable() = 0;	//表
		
		/* 交互 */
		
		/* 挂载变量到Lua
		 * @param 变量引用
		 * @param 该变量在Lua中的名称
		 */
		virtual void MountNumber(int&,const std::string&) = 0;	//挂载数值
		virtual void MountNumber(double&,const std::string&) = 0;
		virtual void MountNumber(float&,const std::string&) = 0;
		virtual void MountString(std::string&,const std::string&) = 0;	//挂载字符串
		virtual void MountBool(bool&,const std::string&) = 0;	//挂载逻辑值
		virtual void MountFunction(void (*func)(LuaVM&),const std::string&) = 0;	//挂载函数
		
		/* 从Lua栈取出栈顶
		 * @result 栈顶元素
		 */
		virtual double PopNumber() = 0;	//取出数值
		virtual std::string PopString() = 0;	//取出字符串
		virtual double PopBoolean() = 0;	//取出逻辑值
		
		/* Lua压栈
		 * @param 栈顶元素
		 */
		virtual void PushNumber(double) = 0;	//压入数值
		virtual void PushString(const std::string&) = 0;	//压入字符串
		virtual void PushBoolean(const std::string&) = 0;	//压入逻辑值
		
		/* 加载和调用代码 */
		
		/* 加载代码
		 * @param 代码内容
		 */
		virtual void LoadProgram(const std::string& code) = 0;
		
		/* 调用函数
		 * 返回值会被放在栈里
		 * @param Lua函数名
		 */
		virtual void Call(const std::string& functionName) = 0;
		
		/* 调用主函数
		 */
		virtual void Call() = 0;
	};
	
	/* 创建Lua虚拟机
	 * @result Lua虚拟机
	 */
	std::shared_ptr<ILuaVM> CreateLuaVM();
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 */
