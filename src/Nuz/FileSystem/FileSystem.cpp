#include "FileSystem.h"
#include "../../../include/Nuz/FileSystem/FileSource.h"
using namespace Nuz_;
using namespace std;
using namespace Nuz;

void FileSystem::Mount(std::shared_ptr<Nuz::IFileSource> source){
    if(m_sources.count(source)){
        throw CannotMountFileSource("Nuz::IFileSystem::Mount()::A source is remounting!");
    }
    m_sources.insert(source);
}

std::shared_ptr<std::vector<uint8_t>> FileSystem::LoadFile(const std::string& path) const{
    if(path.length() <= 1){
         throw InvalidFileName("Nuz::IFileSystem::LoadFile()::Invalid File Name " + path);
    }
    if(path[0] != '/'){
         throw InvalidFileName("Nuz::IFileSystem::LoadFile()::Invalid File Name " + path);
    }

    std::shared_ptr<std::vector<uint8_t>> ret;

    bool read = false;
    for(std::shared_ptr<Nuz::IFileSource> p:m_sources){
        try{
            ret = p -> ReadFile(path);
            read = true;
            break;
        }catch(CannotOpenFile&){
            continue;
        }
    }
    if(!read) throw CannotOpenFile("Nuz::IFileSystem::LoadFile()::Can not open file " + path + ".");
    return ret;
}

