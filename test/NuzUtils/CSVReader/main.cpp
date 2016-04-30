#include <iostream>
#include <memory>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/CSVReader.h"

using namespace std;

int main(){
    auto lf = Nuz::IEngine::GetGameDevice().GetLocalFile(); //获取本地文件系统实例
    Nuz::IEngine::GetGameDevice().GetFileSystem().Mount(lf,"e");    //把本地文件系统挂载到文件系统的目录“e”下
    auto p = NuzUtils::ICSVReader::CreateCSVReader("/e/test/NuzUtils/CSVReader/0.csv"); //从文件创建CSV读取器
    p -> SaveToFastReadFile("/test/NuzUtils/CSVReader/0.elf");  //输出可以快速读取的二进制形式的csv文件
    p = NuzUtils::ICSVReader::CreateCSVReader("/e/test/NuzUtils/CSVReader/0.elf");  //读取二进制形式的csv

    while(!p -> IsLastLine()){  //如果当前不在最后一行
        while(!p -> LineEnd()){ //如果本行没有结束
            cout<<p -> PopString()<<" ";    //输出本元素
        }
        cout<<endl; //输出换行
        p -> NextLine();    //下一行
    }
    cout<<p ->GetCurrentDir();  //获取csv文件所在目录

    return 0;
}