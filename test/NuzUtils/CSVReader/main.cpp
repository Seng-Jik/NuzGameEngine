#include <iostream>
#include <memory>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/CSVReader.h"

using namespace std;

int main(){
    auto lf = Nuz::GetGameDevice().GetLocalFile();
    Nuz::GetGameDevice().GetFileSystem().Mount(lf,"e");
    auto p = NuzUtils::CreateCSVReader("/e/test/NuzUtils/CSVReader/0.csv");
    p -> SaveToFastReadFile("/test/NuzUtils/CSVReader/0.elf");
    p = NuzUtils::CreateCSVReader("/e/test/NuzUtils/CSVReader/0.elf");

    while(!p -> IsLastLine()){
        while(!p -> LineEnd()){
            cout<<p -> PopString()<<" ";
        }
        cout<<endl;
        p -> NextLine();
    }


    return 0;
}
