#include "LocalFile.h"
#include <fstream>
#include <stdexcept>
#include "../../../include/Nuz/FileSystem/FileSystemExceptions.h"

using namespace std;

using namespace Nuz;
using namespace _Nuz;

std::shared_ptr<std::vector<unsigned char> > LocalFile::ReadFile(const std::string& path) const
{
    if(path.length() <=1){
        throw InvalidFileName("Nuz::ILocalFile::ReadFile()::Invalid File Name " + path);
    }
    if(path[0] != '/'){
        throw InvalidFileName("Nuz::ILocalFile::ReadFile()::Invalid File Name " + path);
    }
    ifstream in(path.substr(1,path.length()-1),ios::binary);
    if(!in.good()){
        throw CannotOpenFile("Nuz::ILocalFile::ReadFile()::File "+ path + " Not Found!");
    }
    in.seekg(0,ios::end);
    auto size = in.tellg();
    in.seekg(0,ios::beg);
    std::shared_ptr<std::vector<unsigned char> > buffer(new std::vector<unsigned char>);
    buffer -> resize(size);
    in.read((char*)&(*buffer)[0],size);
    in.close();
    return buffer;
}

unsigned long LocalFile::GetFileSize(const std::string& path) const
{
    if(path.length() <=1){
        throw InvalidFileName("Nuz::ILocalFile::GetFileSize()::Invalid File Name " + path);
    }
    if(path[0] != '/'){
        throw InvalidFileName("Nuz::ILocalFile::GetFileSize()::Invalid File Name " + path);
    }
    ifstream in(path.substr(1,path.length()-1),ios::binary);
    if(!in.good()){
        throw CannotOpenFile("Nuz::ILocalFile::GetFileSize()::File "+ path + " Not Found!");
    }
    in.seekg(0,ios::end);
    long size = in.tellg();
    in.close();
    return size;
}

void LocalFile::SaveFile(const std::shared_ptr<std::vector<unsigned char> > buffer, const std::string path) const
{
    if(path.length() <=1){
        throw InvalidFileName("Nuz::ILocalFile::SaveFile()::Invalid File Name " + path);
    }
    if(path[0] != '/'){
        throw InvalidFileName("Nuz::ILocalFile::SaveFile()::Invalid File Name " + path);
    }
    ofstream out(path.substr(1,path.length()-1),ios::binary);
    if(!out.good()){
        throw CannotOpenFile("Nuz::ILocalFile::SaveFile()::File "+ path + " Can not saved.");
    }
    out.write((char*)(&(*buffer)[0]),buffer -> size());
    out.close();
}

void LocalFile::CopyFile(const std::string& src, const std::string& dst) const
{
    try{
        std::shared_ptr<std::vector<unsigned char> > buf = LocalFile::ReadFile(src);
        LocalFile::SaveFile(buf,dst);
    }catch(CannotOpenFile){
        throw runtime_error("Nuz::ILocalFile::CopyFile()::Can not copy " + src + " to " + dst);
    }catch(InvalidFileName& e){
        throw InvalidFileName(string("Nuz::ILocalFile::CopyFile()::Invaild File Name ") + string("\n\t") + e.what());
    }
}

