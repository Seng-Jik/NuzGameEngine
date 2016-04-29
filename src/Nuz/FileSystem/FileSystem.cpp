#include "FileSystem.h"
#include "../../../include/Nuz/FileSystem/FileSource.h"
using namespace Nuz_;
using namespace std;
using namespace Nuz;

void FileSystem::Mount(const std::shared_ptr<const Nuz::IFileSource>& source,const std::string& dir){
    m_sources[dir] = source;
}

std::shared_ptr<std::vector<uint8_t>> FileSystem::LoadFile(const std::string& path) const{
    if(path.length() <= 1){
         throw InvalidFileName("Invalid File Name " + path);
    }
    if(path[0] != '/'){
         throw InvalidFileName("Invalid File Name " + path);
    }

    //Find dir
    auto nextPos = path.find('/',1);    //Find sub dir symbol '/'
    if(nextPos != string::npos){    //If it has a sub dir symbol
        string dir = path.substr(1,nextPos-1);  //Find lv1 sub dir.
        if(m_sources.count(dir)){   //If source found.
            try{    //Try to load file and return.
                auto ret = m_sources.at(dir) -> ReadFile(path.substr(nextPos,path.length()-nextPos));
                return ret;
            }catch(CannotOpenFile&){
            }
        }
    }
    if(m_sources.count("") == 0) throw CannotOpenFile("File " + path + " not found.");
    auto ret = m_sources.at("") ->ReadFile(path);
    return ret;
}

std::string IFileSystem::GetUpperDir(const std::string& path){
    if(path.length() <= 1){
         throw IFileSystem::InvalidFileName("Invalid File Name " + path);
    }
    if(path[0] != '/'){
         throw IFileSystem::InvalidFileName("Invalid File Name " + path);
    }
    auto pos = path.rfind('/');
    return path.substr(0,pos);
}
