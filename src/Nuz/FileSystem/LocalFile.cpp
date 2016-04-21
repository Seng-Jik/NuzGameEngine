#include "LocalFile.h"
#include <fstream>
#include <stdexcept>
#include "FileSystemExceptions.h"

using namespace std;


using namespace _Nuz;

std::shared_ptr<std::vector<unsigned char> > LocalFile::ReadFile(const std::string& path, unsigned long& size) const
{
    if(path[0] != '/'){
        throw Invalid_FileName("Nuz::ILocalFile::ReadFile()::Invalid File Name " + path);
    }
    ifstream in(path.substr(1,path.length()-1),ios::binary);
    if(!in.good()){
        throw Cannot_OpenFile("Nuz::ILocalFile::ReadFile()::File "+ path + " Not Found!");
    }
    in.seekg(0,ios::end);
    size = in.tellg();
    in.seekg(0,ios::beg);
    std::shared_ptr<std::vector<unsigned char> > buffer(new std::vector<unsigned char>);
    buffer -> resize(size);
    in.read((char*)&(*buffer)[0],size);
    in.close();
    return buffer;
}

unsigned long LocalFile::GetFileSize(const std::string& path) const
{
    if(path[0] != '/'){
        throw Invalid_FileName("Nuz::ILocalFile::GetFileSize()::Invalid File Name " + path);
    }
    ifstream in(path.substr(1,path.length()-1),ios::binary);
    if(!in.good()){
        throw Cannot_OpenFile("Nuz::ILocalFile::GetFileSize()::File "+ path + " Not Found!");
    }
    in.seekg(0,ios::end);
    long size = in.tellg();
    in.close();
    return size;
}

void LocalFile::SaveFile(const std::shared_ptr<std::vector<unsigned char> > buffer, const std::string path) const
{
    if(path[0] != '/'){
        throw Invalid_FileName("Nuz::ILocalFile::SaveFile()::Invalid File Name " + path);
    }
    ofstream out(path.substr(1,path.length()-1),ios::binary);
    if(!out.good()){
        throw Cannot_OpenFile("Nuz::ILocalFile::SaveFile()::File "+ path + " Can not saved.");
    }
    out.write((char*)(&(*buffer)[0]),buffer -> size());
    out.close();
}

void LocalFile::CopyFile(const std::string& src, const std::string& dst) const
{
    unsigned long size;
    try{
        std::shared_ptr<std::vector<unsigned char> > buf = LocalFile::ReadFile(src,size);
        LocalFile::SaveFile(buf,dst);
    }catch(Cannot_OpenFile){
        throw runtime_error("Nuz::ILocalFile::CopyFile()::Can not copy " + src + " to " + dst);
    }catch(Invalid_FileName& e){
        throw Invalid_FileName(string("Nuz::ILocalFile::CopyFile()::Invaild File Name ") + string("\n\t") + e.what());
    }
}

