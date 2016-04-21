#include "Engine.h"

using namespace _Nuz;
using namespace Nuz;
Nuz::IFileSystem& Engine::GetFileSystem()
{
    return m_fileSystem;
}

Nuz::ILocalFile& Engine::GetLocalFile()
{
    return m_localFile;
}

std::shared_ptr<IEngine> Nuz::CreateGameDevice(const char* title,bool fullScreen,int w,int h){
    return std::shared_ptr<IEngine>(new Engine);
}

