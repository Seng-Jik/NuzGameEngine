#include <iostream>
#include <memory>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/CSVReader.h"

using namespace std;

int main(){
    Nuz::CreateGameDevice("",false);
    shared_ptr<Nuz::IFileSource> lf = shared_ptr<Nuz::IFileSource>(&Nuz::GetGameDevice().GetLocalFile());
    Nuz::GetGameDevice().GetFileSystem().Mount(lf);
    auto p = NuzUtils::CreateCSVReader("/TestCSVReader.csv");
    p -> SaveToFastReadFile("/TestCSVReader.cso");
    p = NuzUtils::CreateCSVReader("/TestCSVReader.cso");

    while(!p -> IsLastLine()){
        while(!p -> LineEnd()){
            cout<<p -> PopString()<<" ";
        }
        cout<<endl;
        p -> NextLine();
    }


    return 0;
}
