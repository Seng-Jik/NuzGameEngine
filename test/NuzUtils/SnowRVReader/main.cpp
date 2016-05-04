#include <iostream>
#include <memory>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/SnowRVReader.h"
using namespace std;

int main(){
    auto lf = Nuz::IEngine::GetGameDevice().GetLocalFile(); //获取本地文件系统
    Nuz::IEngine::GetGameDevice().GetFileSystem().Mount(lf,"testSet");  //挂载本地文件系统到文件系统的“testSet”目录下
    auto p = NuzUtils::ISnowRVReader::CreateSnowRVReader("/testSet/test/NuzUtils/SnowRVReader/test.rv");    //从文件创建SnowRV阅读器
    p -> SaveToBinaryFile("/test/NuzUtils/SnowRVReader/test.elf");    //保存到二进制码
    p = NuzUtils::ISnowRVReader::CreateSnowRVReader("/testSet/test/NuzUtils/SnowRVReader/test.elf");    //从二进制码创建SnowRV阅读器

    cout<<p -> GetInt("RVI")<<endl; //获取整型常量RVI
    cout<<p -> GetString("RVS")<<endl;  //获取字符串常量RVS
    cout<<p -> GetFloat("KEC")<<endl;   //获取浮点型常量KEC
    cout<<p -> GetCurrentDir()<<endl;   //获取RV文件所在目录
    return 0;
}
