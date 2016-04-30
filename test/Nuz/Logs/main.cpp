#include "../../../include/Nuz/Logs.h"
#include <iostream>
using namespace std;
using namespace Nuz;

int main(){
    SetStdLogOutputStream(cout);    //设置普通日志输出流
    AddStdLogWhiteFliter("Module1");    //添加Module1模块的白名单
    LogStd("Log1","Module1");   //Module1模块的日志，输出
    LogStd("Log2","Module2");   //Module2模块的日志，没添加到白名单，不会输出
    LogStd("Log3"); //未知模块的日志，因为不确定是哪个模块输出的，所以会输出

    SetErrLogOutputStream(cout);    //设置错误日志输出流
    AddErrLogBlackFliter("ErrMod1");    //添加错误日志黑名单，模块ErrMod1
    LogErr("ErrMod1","ErrMod1");    //ErrMod1模块输出的错误日志，因为有黑名单，所以不输出
    LogErr("ErrMod2","ErrMod2");    //ErrMod2模块输出的错误日志，输出
    LogErr("ErrMod3");  //未知模块的错误日志，输出

    return 0;
}