#include "FileSystem.h"
#include "../../../include/Nuz/FileSystem/FileSource.h"
#include "../../../include/Nuz/FileSystem/FileSystemExceptions.h"
using namespace _Nuz;
using namespace std;
using namespace Nuz;

void FileSystem::Mount(std::shared_ptr<Nuz::IFileSource> source){
    if(m_sources.count(source)){
        throw runtime_error("Nuz::IFileSystem::Mount()::A source is remounting!");
    }
    m_sources.insert(source);
}

std::shared_ptr<std::vector<unsigned char>> FileSystem::LoadFile(const std::string& path) const{
    if(path.length() <= 1){
         throw InvalidFileName("Nuz::IFileSystem::LoadFile()::Invalid File Name " + path);
    }
    if(path[0] != '/'){
         throw InvalidFileName("Nuz::IFileSystem::LoadFile()::Invalid File Name " + path);
    }

    std::shared_ptr<std::vector<unsigned char>> ret;

    for(std::shared_ptr<Nuz::IFileSource> p:m_sources){
        try{
            ret = p -> ReadFile(path);
            break;
        }catch(CannotOpenFile&){
            continue;
        }
    }
    return ret;
}

