#include "LuaVM.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"

using namespace Nuz_Utils;
using namespace NuzUtils;

LuaVM::LuaVM(){
    m_vm = luaL_newstate();
    if(!m_vm) throw CannotCreateLuaVM("NuzUtils::CreateLuaVM()::Lua State Create failed.");
    luaopen_base(m_vm);
    #ifdef _DEBUG
    luaopen_debug(m_vm);
    #endif // _DEBUG
}

LuaVM::~LuaVM(){
    lua_close(m_vm);
}

void LuaVM::OpenLibMath(){luaopen_math(m_vm);}
void LuaVM::OpenLibIO(){luaopen_io(m_vm);}
void LuaVM::OpenLibString(){luaopen_string(m_vm);}
void LuaVM::OpenLibTable(){luaopen_table(m_vm);}

void LuaVM::MountNumber(int& i,const std::string& s){m_mint[s] = &i;}
void LuaVM::MountNumber(double& d,const std::string& s){m_mdbl[s] = &d;}
void LuaVM::MountNumber(float& f,const std::string& s){m_mflt[s] = &f;}
void LuaVM::MountString(std::string& str,const std::string& s){m_mstr[s] = &str;}
void LuaVM::MountBool(bool& b,const std::string& s){m_mbool[s] = &b;}
void LuaVM::MountFunction(int (*func)(lua_State*),const std::string& s){
    lua_pushcfunction(m_vm,func);
    lua_setglobal(m_vm,s.c_str());
}

void LuaVM::LoadProgram(const std::string& code){
    luaL_loadbuffer(m_vm,code.c_str(),code.size(),"NuzUtils::LuaVM::LoadProgram()");
}

void LuaVM::LoadProgramFromFile(const std::string& file){
    auto buf = Nuz::GetGameDevice().GetFileSystem().LoadFile(file);
    luaL_loadbuffer(m_vm,(char*)(&(*buf)[0]),buf->size(),"NuzUtils::LuaVM::LoadProgramFromFile()");
}

void LuaVM::Call(const std::string& functionName,int argc,int nresults){
    syncSend();
    lua_getglobal(m_vm,functionName.c_str());
    lua_call(m_vm,argc,nresults);
    syncGet();
}
void LuaVM::Call(){
    syncSend();
    lua_call(m_vm,0,0);
    syncGet();
}
lua_State* LuaVM::GetLuaState(){
    return m_vm;
}

void LuaVM::syncSend(){
    for(std::pair<const std::string,int*>& i:m_mint){
        lua_pushinteger(m_vm,*i.second);
        lua_setglobal(m_vm,i.first.c_str());
    }
    for(std::pair<const std::string,double*>& i:m_mdbl){
        lua_pushnumber(m_vm,*i.second);
        lua_setglobal(m_vm,i.first.c_str());
    }
    for(std::pair<const std::string,float*>& i:m_mflt){
        lua_pushnumber(m_vm,*i.second);
        lua_setglobal(m_vm,i.first.c_str());
    }
    for(std::pair<const std::string,std::string*>& i:m_mstr){
        lua_pushstring(m_vm,i.second->c_str());
        lua_setglobal(m_vm,i.first.c_str());
    }
    for(std::pair<const std::string,bool*>& i:m_mbool){
        lua_pushboolean(m_vm,*i.second);
        lua_setglobal(m_vm,i.first.c_str());
    }
}

void LuaVM::syncGet(){
    for(std::pair<const std::string,int*>& i:m_mint){
        lua_getglobal(m_vm,i.first.c_str());
        *i.second = lua_tointeger(m_vm,-1);
        lua_pop(m_vm,1);
    }
    for(std::pair<const std::string,double*>& i:m_mdbl){
        lua_getglobal(m_vm,i.first.c_str());
        *i.second = lua_tonumber(m_vm,-1);
        lua_pop(m_vm,1);
    }
    for(std::pair<const std::string,float*>& i:m_mflt){
        lua_getglobal(m_vm,i.first.c_str());
        *i.second = lua_tonumber(m_vm,-1);
        lua_pop(m_vm,1);
    }
    for(std::pair<const std::string,std::string*>& i:m_mstr){
        lua_getglobal(m_vm,i.first.c_str());
        *i.second = lua_tostring(m_vm,-1);
        lua_pop(m_vm,1);
    }
    for(std::pair<const std::string,bool*>& i:m_mbool){
        lua_getglobal(m_vm,i.first.c_str());
        *i.second = lua_toboolean(m_vm,-1);
        lua_pop(m_vm,1);
    }
}

std::shared_ptr<ILuaVM> NuzUtils::CreateLuaVM(){
    return std::shared_ptr<ILuaVM>(new LuaVM);
}
