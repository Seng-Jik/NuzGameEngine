#include "../../../../src/Nuz/FileSystem/LocalFile.h"
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace _Nuz;
int main(){
    LocalFile localFile;

    try{
        unsigned long size;
        localFile.CopyFile("/0.aif","/1.aif");
        cout<<localFile.GetFileSize("/0.aif");
    }
    catch(runtime_error& e){
        cout<<e.what()<<endl;
    }
    catch(invalid_argument& e){
        cout<<e.what()<<endl;
    }
    return 0;
}
