#include "../../include/Nuz/Logs.h"
#include <set>
#include <iostream>
using namespace std;
namespace Nuz{
    #ifdef _DEBUG
    static set<string> stdWhiteFliter;
    static ostream* stdLogOut = &cout;

    void LogStd(const std::string& log,const std::string& module){
        if(stdWhiteFliter.count(module) || module.empty()){
            (*stdLogOut)<<"StdLog:"<<module<<":"<<log<<endl;
        }
    }

    void SetStdLogOutputStream(std::ostream& s) noexcept{
        stdLogOut = &s;
    }

    void AddStdLogWhiteFliter(const std::string& module){
        stdWhiteFliter.insert(module);
    }

    void ClearStdLogWhiteFliter(){
        stdWhiteFliter.clear();
    }

    #endif // _DEBUG

    static set<string> errBlackFliter;
    static ostream* errLogOut = &cout;

    void LogErr(const std::string& log,const std::string& module){
        if(!errBlackFliter.count(module)){
            (*errLogOut)<<"ErrLog:"<<module<<":"<<log<<endl;
        }
    }

    void SetErrLogOutputStream(std::ostream& e) noexcept{
        errLogOut = &e;
    }

    void AddErrLogBlackFliter(const std::string& module){
        errBlackFliter.insert(module);
    }

    void ClearErrLogBlackFliter(){
        errBlackFliter.clear();
    }

}
