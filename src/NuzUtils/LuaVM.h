#pragma once
#include <memory>
#include <string>
#include <lua.hpp>
#include <vector>
#include "../../include/NuzUtils/LuaVM.h"
namespace _NuzUtils{

	class LuaVM:public NuzUtils::ILuaVM{
    private:
        lua_State* m_vm;

        template<class T> struct MountedData{
            T* org;
            std::string name;
        };
        std::vector<MountedData<int> > m_mint;
        std::vector<MountedData<double> > m_mdbl;
        std::vector<MountedData<float> > m_mflt;
        std::vector<MountedData<std::string> > m_mstr;
        std::vector<MountedData<bool> > m_mbool;
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
