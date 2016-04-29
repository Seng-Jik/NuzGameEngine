#include "../../include/Nuz/Logs.h"
#include <set>
#include <iostream>
#include <mutex>
using namespace std;
namespace Nuz{
    static std::mutex stdlock;
    static set<string> stdWhiteFliter;
    static ostream* stdLogOut = &cout;

    void LogStd(const std::string& log,const std::string& module){
        lock_guard<mutex> g(stdlock);
        if(stdWhiteFliter.count(module) || module.empty()){
            (*stdLogOut)<<"StdLog:"<<module<<":"<<log<<endl;
        }
    }

    void SetStdLogOutputStream(std::ostream& s) noexcept{
        lock_guard<mutex> g(stdlock);
        stdLogOut = &s;
    }

    void AddStdLogWhiteFliter(const std::string& module){
        lock_guard<mutex> g(stdlock);
        stdWhiteFliter.insert(module);
    }

    void ClearStdLogWhiteFliter(){
        lock_guard<mutex> g(stdlock);
        stdWhiteFliter.clear();
    }

    static set<string> errBlackFliter;
    static ostream* errLogOut = &cout;
    static std::mutex errlock;

    void LogErr(const std::string& log,const std::string& module){
        lock_guard<mutex> g(errlock);
        if(!errBlackFliter.count(module)){
            (*errLogOut)<<"ErrLog:"<<module<<":"<<log<<endl;
        }
    }

    void SetErrLogOutputStream(std::ostream& e) noexcept{
        lock_guard<mutex> g(errlock);
        errLogOut = &e;
    }

    void AddErrLogBlackFliter(const std::string& module){
        lock_guard<mutex> g(errlock);
        errBlackFliter.insert(module);
    }

    void ClearErrLogBlackFliter(){
        lock_guard<mutex> g(errlock);
        errBlackFliter.clear();
    }

}
