#include "../../../../include/Nuz.h"    //Nuz引擎头文件
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
using namespace std;
using namespace Nuz;    //Nuz引擎命名空间
int main(){
    IEngine& engine = IEngine::GetGameDevice(); //取得引擎实例
    IFileSystem& fs = engine.GetFileSystem();   //取得文件系统
    auto lf = engine.GetLocalFile();    //取得本地文件系统

    fs.Mount(shared_ptr<IFileSource>(lf));  //把本地文件系统挂载到文件系统的根目录

    auto buf = fs.LoadFile("/test/Nuz/FileSystem/FileSystem/0.txt");    //从文件系统获取文件

    ofstream out("test/Nuz/FileSystem/FileSystem/1.txt",ios::binary);   //写出文件
    out.write((char*)&((*buf)[0]),buf -> size());
    out.close();

    fs.Mount(shared_ptr<IFileSource>(lf));  //再次挂载

    return 0;
}