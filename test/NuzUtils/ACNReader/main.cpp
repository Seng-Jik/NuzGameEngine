#include <iostream>
#include <memory>
#include <string>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/ACNReader.h"

using namespace std;

int main(){
    auto lf = Nuz::IEngine::GetGameDevice().GetLocalFile(); //获取本地文件系统实例
    Nuz::IEngine::GetGameDevice().GetFileSystem().Mount(lf,"e");    //把本地文件系统挂载到文件系统的目录“e”下
    auto acn = NuzUtils::IACNReader::CreateACNReader("/e/test/NuzUtils/ACNReader/test.acn");   //加载acn文件

    while(1){
        std::string arg;
        auto opr = acn -> GetOpr(arg);
        cout<<"ACN OPR:"<<int(opr)<<" "<<arg<<endl;
        if(opr == NuzUtils::IACNReader::ACNOpr::End) break;
    }
    return 0;
}
