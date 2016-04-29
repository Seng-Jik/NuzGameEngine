#include <iostream>
#include <memory>
#include "../../../include/Nuz.h"
#include "../../../include/NuzUtils/CSVReader.h"

using namespace std;

int main(){
    auto lf = Nuz::IEngine::GetGameDevice().GetLocalFile();
    Nuz::IEngine::GetGameDevice().GetFileSystem().Mount(lf,"e");
    auto p = NuzUtils::ICSVReader::CreateCSVReader("/e/test/NuzUtils/CSVReader/0.csv");
    p -> SaveToFastReadFile("/test/NuzUtils/CSVReader/0.elf");
    p = NuzUtils::ICSVReader::CreateCSVReader("/e/test/NuzUtils/CSVReader/0.elf");

    while(!p -> IsLastLine()){
        while(!p -> LineEnd()){
            cout<<p -> PopString()<<" ";
        }
        cout<<endl;
        p -> NextLine();
    }
    cout<<p ->GetCurrentDir();

    return 0;
}
