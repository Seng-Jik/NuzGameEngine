#include <iostream>
#include <memory>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/SnowRVReader.h"
using namespace std;

int main(){
    auto lf = Nuz::GetGameDevice().GetLocalFile();
    Nuz::GetGameDevice().GetFileSystem().Mount(lf,"testSet");
    auto p = NuzUtils::CreateSnowRVReader("/testSet/test/NuzUtils/SnowRVReader/test.rv");
    p -> SaveToFastReadFile("/test/NuzUtils/SnowRVReader/test.elf");
    p = NuzUtils::CreateSnowRVReader("/testSet/test/NuzUtils/SnowRVReader/test.elf");

    cout<<p -> GetInt("RVI")<<endl;
    cout<<p -> GetString("RVS")<<endl;
    cout<<p -> GetFloat("KEC")<<endl;
    //cout<<p -> GetFloat("233")<<endl;

    return 0;
}
