#include "../../../../include/Nuz.h"
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <memory>
using namespace std;
using namespace Nuz;
int main(){
    shared_ptr<vector<uint8_t> > b(new vector<uint8_t>);    //新建缓存区
    b ->push_back('H');
    b ->push_back('e');
    b ->push_back('l');
    b ->push_back('l');
    b ->push_back('o');
    b ->push_back('W');
    b ->push_back('o');
    b ->push_back('r');
    b ->push_back('l');
    b ->push_back('d');

    Nuz::IEngine::GetGameDevice().GetLocalFile() -> SaveFile(b,"/test/Nuz/FileSystem/LocalFile/0.txt"); //保存到文件

    return 0;
}