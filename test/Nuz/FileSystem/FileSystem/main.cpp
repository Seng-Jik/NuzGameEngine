#include "../../../../include/Nuz.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
using namespace std;
using namespace Nuz;
int main(){
    auto engine = CreateGameDevice("FFF",false);
    IFileSystem& fs = engine -> GetFileSystem();
    ILocalFile& lf = engine -> GetLocalFile();

    fs.Mount(shared_ptr<IFileSource>(&lf));

    auto buf = fs.LoadFile("/0.aif");

    ofstream out("1.aif",ios::binary);
    out.write((char*)&((*buf)[0]),buf -> size());

    fs.Mount(shared_ptr<IFileSource>(&lf));

    return 0;
}
