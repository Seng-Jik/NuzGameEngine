#pragma once
#include <memory>
#include <string>
#include <lua.hpp>
#include <vector>
#include <map>
#include <mutex>
#include "../../include/NuzUtils/LuaVM.h"
namespace NuzUtils_{

	class LuaVM:public NuzUtils::ILuaVM{
    private:
        lua_State* m_vm;

        std::map<std::string,int*> m_mint;
        std::map<std::string,double*> m_mdbl;
        std::map<std::string,float*> m_mflt;
        std::map<std::string,std::string*> m_mstr;
        std::map<std::string,bool*> m_mbool;
        std::mutex m_lock;

        void syncSend();
        void syncGet();
	public:
	    LuaVM();
	    ~LuaVM();
        void OpenLibMath() override;
		void OpenLibIO() override;
		void OpenLibString() override;
		void OpenLibTable() override;
		void MountNumber(int&,const std::string&) override;
		void MountNumber(double&,const std::string&) override;
		void MountNumber(float&,const std::string&) override;
		void MountString(std::string&,const std::string&) override;
		void MountBool(bool&,const std::string&) override;
		void MountFunction(int (*func)(lua_State*),const std::string&) override;
		void LoadProgram(const std::string& code) override;
        void LoadProgramFromFile(const std::string&) override;
		void Call(const std::string& functionName,int argc,int nresults) override;
		void Call() override;
		lua_State* GetLuaState() override;
	};
}
