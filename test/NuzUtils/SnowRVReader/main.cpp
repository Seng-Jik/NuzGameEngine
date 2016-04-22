#include <iostream>
#include <memory>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/SnowRVReader.h"
using namespace std;

int main(){
    Nuz::CreateGameDevice("",false);
    shared_ptr<Nuz::IFileSource> lf = shared_ptr<Nuz::IFileSource>(&Nuz::GetGameDevice().GetLocalFile());
    Nuz::GetGameDevice().GetFileSystem().Mount(lf);
    auto p = NuzUtils::CreateSnowRVReader("/test.txt");
    p -> SaveToFastReadFile("/test.rvo");
    p = NuzUtils::CreateSnowRVReader("/test.rvo");

    cout<<p -> GetInt("RVI")<<endl;
    cout<<p -> GetString("RVS")<<endl;
    cout<<p -> GetFloat("KEC")<<endl;
    //cout<<p -> GetFloat("233")<<endl;

    return 0;
}
