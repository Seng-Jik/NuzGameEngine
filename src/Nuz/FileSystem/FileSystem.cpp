#include "FileSystem.h"

using namespace _Nuz;
using namespace Nuz;

void FileSystem::Mount(const std::string& name,const std::string& dir,std::shared_ptr<Nuz::IFileSource> source){
    if(m_name_sources.count(name)){
        throw std::runtime_error("Nuz::IFileSystem::Mount()::File sources "+ name +" has been mounted.");
    }
    m_name_sources[name] = source;
    m_dir_sources[dir] = source;
}

void FileSystem::Mount(const std::string& name,const std::string& dir,std::shared_ptr<Nuz::IFileSource> source){
    if(m_name_sources.count(name)){
        throw std::runtime_error("Nuz::IFileSystem::Mount()::File sources "+ name +" has been mounted.");
    }
    m_name_sources[name] = source;
    m_dir_sources[dir] = source;
}

void FileSystem::Unmount(const std::string& name){
    if(m_name_sources.count(name)){
        throw std::runtime_error("Nuz::IFileSystem::Mount()::File sources "+ name +" has been mounted.");
    }
    m_name_sources[name] = source;
    m_dir_sources[dir] = source;
}

