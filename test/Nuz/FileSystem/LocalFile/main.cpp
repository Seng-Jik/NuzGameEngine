#include "../../../../src/Nuz/FileSystem/LocalFile.h"
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace _Nuz;
int main(){
    LocalFile localFile;

    localFile.CopyFile("/0.aif","/1.aif");
    cout<<localFile.GetFileSize("/0.aif");


    return 0;
}
