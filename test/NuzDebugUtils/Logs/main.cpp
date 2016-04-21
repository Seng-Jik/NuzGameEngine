#include "../../../include/NuzDebugUtils/Logs.h"
#include <iostream>
using namespace std;

int main(){
    SetStdLogOutputStream(cout);
    AddStdLogWhiteFliter("Module1");
    LogStd("Log1","Module1");
    LogStd("Log2","Module2");
    LogStd("Log3");

    SetErrLogOutputStream(cout);
    AddErrLogBlackFliter("ErrMod1");
    LogErr("ErrMod1","ErrMod1");
    LogErr("ErrMod2","ErrMod2");
    LogErr("ErrMod3");

    return 0;
}
