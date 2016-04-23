#pragma once
#include <memory>
#include <string>
#include <lua.hpp>
#include <vector>
#include <map>
#include "../../include/NuzUtils/LuaVM.h"
namespace _NuzUtils{

	class LuaVM:public NuzUtils::ILuaVM{
    private:
        lua_State* m_vm;

        std::map<std::string,int*> m_mint;
        std::map<std::string,double*> m_mdbl;
        std::map<std::string,float*> m_mflt;
        std::map<std::string,std::string*> m_mstr;
        std::map<std::string,bool*> m_mbool;

        void syncSend();
        void syncGet();
	public:
	    LuaVM();
	    virtual ~LuaVM();
		virtual void OpenLibMath();
		virtual void OpenLibIO();
		virtual void OpenLibString();
		virtual void OpenLibTable();
		virtual void MountNumber(int&,const std::string&);
		virtual void MountNumber(double&,const std::string&);
		virtual void MountNumber(float&,const std::string&);
		virtual void MountString(std::string&,const std::string&);
		virtual void MountBool(bool&,const std::string&);
		virtual void MountFunction(int (*func)(lua_State*),const std::string&);
		virtual void LoadProgram(const std::string& code);
        virtual void LoadProgramFromFile(const std::string&);
		virtual void Call(const std::string& functionName,int argc,int nresults);
		virtual void Call();
		virtual lua_State* GetLuaState();
	};
}
