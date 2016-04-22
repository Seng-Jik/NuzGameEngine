#pragma once
#include <memory>
#include <string>

struct lua_State;
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
		 * 要挂载的变量必须长期存在
		 * @param 变量引用
		 * @param 该变量在Lua中的名称
		 */
		virtual void MountNumber(int&,const std::string&) = 0;	//挂载数值
		virtual void MountNumber(double&,const std::string&) = 0;
		virtual void MountNumber(float&,const std::string&) = 0;
		virtual void MountString(std::string&,const std::string&) = 0;	//挂载字符串
		virtual void MountBool(bool&,const std::string&) = 0;	//挂载逻辑值

		/* 挂载函数到Lua
		 * @param func C函数（见Lua文档）
		 * @param 它在Lua程序中的名称
		 */
		virtual void MountFunction(int(*func)(lua_State*),const std::string&) = 0;	//挂载函数

		/* 加载和调用代码 */

		/* 加载代码
		 * @param code 代码内容
		 */
		virtual void LoadProgram(const std::string& code) = 0;

		/* 加载代码（从文件）
		 * @param 文件名
		 * @throw Nuz::CannotOpenFile
		 * @throw Nuz::InvaildFileName
		 */
        virtual void LoadProgramFromFile(const std::string&) = 0;

		/* 调用函数
		 * 返回值会被放在栈里
		 * @param functionName Lua函数名
         * @param argc 参数个数
         * @param nresults 返回值个数
		 */
		virtual void Call(const std::string& functionName,int argc,int nresults) = 0;

		/* 调用主函数
		 */
		virtual void Call() = 0;

		/* 取得Lua虚拟机指针
		 * @result lua_State* 指针
		 */
        virtual lua_State* GetLuaState() = 0;
	};

	/* 创建Lua虚拟机
	 * @result Lua虚拟机
	 */
	std::shared_ptr<ILuaVM> CreateLuaVM();
}

/* 更新日志：
 * 2016年4月19日：
 * 星翼 初稿
 * 星翼 允许从文件加载
 */
