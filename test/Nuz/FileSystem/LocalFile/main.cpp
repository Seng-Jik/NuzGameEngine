#include "../../../../src/Nuz/FileSystem/LocalFile.h"
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace Nuz_;
int main(){
    LocalFile localFile;

    localFile.CopyFile("/test/Nuz/FileSystem/LocalFile/0.txt","/test/Nuz/FileSystem/LocalFile/1.txt");
    cout<<localFile.GetFileSize("/test/Nuz/FileSystem/LocalFile/1.txt");


    return 0;
}
