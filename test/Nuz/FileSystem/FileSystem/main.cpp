#include "../../../../include/Nuz.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
using namespace std;
using namespace Nuz;
int main(){
    IEngine& engine = GetGameDevice();
    IFileSystem& fs = engine.GetFileSystem();
    ILocalFile& lf = engine.GetLocalFile();

    //fs.Mount(shared_ptr<IFileSource>(&lf));

    auto buf = fs.LoadFile("/test/Nuz/FileSystem/FileSystem/0.txt");

    ofstream out("/test/Nuz/FileSystem/FileSystem/1.txt",ios::binary);
    out.write((char*)&((*buf)[0]),buf -> size());

    fs.Mount(shared_ptr<IFileSource>(&lf));

    return 0;
}
