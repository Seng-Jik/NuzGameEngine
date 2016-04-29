#include "LocalFile.h"
#include "../../../include/Nuz/FileSystem/FileSystem.h"
#include <fstream>
#include <stdexcept>

using namespace std;

using namespace Nuz;
using namespace Nuz_;

std::shared_ptr<std::vector<uint8_t> > LocalFile::ReadFile(const std::string& path) const
{
    if(path.length() <=1){
        throw IFileSystem::InvalidFileName("Invalid File Name " + path);
    }
    if(path[0] != '/'){
        throw IFileSystem::InvalidFileName("Invalid File Name " + path);
    }
    ifstream in(path.substr(1,path.length()-1),ios::binary);
    if(!in.good()){
        throw IFileSystem::CannotOpenFile("File "+ path + " Not Found!");
    }
    in.seekg(0,ios::end);
    auto size = in.tellg();
    in.seekg(0,ios::beg);
    std::shared_ptr<std::vector<uint8_t> > buffer(new std::vector<uint8_t>);
    buffer -> resize(size);
    in.read((char*)&(*buffer)[0],size);
    in.close();
    return buffer;
}

void LocalFile::SaveFile(const std::shared_ptr<const std::vector<uint8_t> >& buffer, const std::string& path) const
{
    if(path.length() <=1){
        throw IFileSystem::InvalidFileName("Invalid File Name " + path);
    }
    if(path[0] != '/'){
        throw IFileSystem::InvalidFileName("Invalid File Name " + path);
    }
    ofstream out(path.substr(1,path.length()-1),ios::binary);
    if(!out.good()){
        throw IFileSystem::CannotOpenFile("File "+ path + " Can not saved.");
    }
    out.write((char*)(&(*buffer)[0]),buffer -> size());
    out.close();
}

