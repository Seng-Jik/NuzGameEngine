#include <iostream>
#include <memory>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/LuaVM.h"
#include <string>
#include <lua.hpp>
using namespace std;
int i = 0;  //Lua脚本里会被使用的几个变量
float k = 1;
double s = 2;
string str = "asda";
bool b = true;

int f(lua_State* s){    //Lua脚本里要调用的C函数
    cout<<endl<<"Func f"<<endl;
}

int main(){
    auto lf = Nuz::IEngine::GetGameDevice().GetLocalFile(); //获取本地文件系统
    Nuz::IEngine::GetGameDevice().GetFileSystem().Mount(lf,"test"); //挂载到文件系统的“test”目录下
    auto p = NuzUtils::ILuaVM::CreateLuaVM();   //创建Lua虚拟机
    p -> OpenLibIO();   //添加标准库
    p -> OpenLibString();
    p -> MountNumber(i,"x");    //挂载C++变量到Lua虚拟机
    p -> MountNumber(k,"x2");
    p -> MountNumber(s,"x3");
    p -> MountString(str,"str");
    p -> MountFunction(&f,"f");
    p -> MountBool(b,"b");
    p -> LoadProgramFromFile("/test/test/NuzUtils/LuaVM/lua.lua");  //加载Lua程序
    p -> Call();    //调用Lua主程序
    p -> LoadProgram("x = 123");    //从字符串加载Lua程序
    p -> Call();    //调用Lua主程序
    p -> Call("flua",0,0);  //调用Lua程序的flua函数

    cout<<i<<k<<s<<str<<b<<endl;    //输出各变量
    return 0;
}