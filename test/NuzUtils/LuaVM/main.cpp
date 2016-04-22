#include <iostream>
#include <memory>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/LuaVM.h"
#include <string>
#include <lua.hpp>
using namespace std;
int i = 0;
float k = 1;
double s = 2;
string str = "asda";
bool b = true;

int f(lua_State* s){
    cout<<endl<<"Func f"<<endl;
}

int main(){
    Nuz::CreateGameDevice("",false);
    shared_ptr<Nuz::IFileSource> lf = shared_ptr<Nuz::IFileSource>(&Nuz::GetGameDevice().GetLocalFile());
    Nuz::GetGameDevice().GetFileSystem().Mount(lf);
    auto p = NuzUtils::CreateLuaVM();
    p -> OpenLibIO();
    p -> OpenLibString();
    p -> MountNumber(i,"x");
    p -> MountNumber(k,"x2");
    p -> MountNumber(s,"x3");
    p -> MountString(str,"str");
    p -> MountFunction(&f,"f");
    p -> MountBool(b,"b");
    p -> LoadProgramFromFile("/test/NuzUtils/LuaVM/lua.lua");
    p -> Call();
    p -> LoadProgram("x = 123");
    p -> Call();
    p -> Call("flua",0,0);

    cout<<i<<k<<s<<str<<b<<endl;
    return 0;
}
