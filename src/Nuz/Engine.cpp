#include "Engine.h"
#include <memory>
using namespace _Nuz;
using namespace Nuz;

_Nuz::Engine* engine = nullptr;

Nuz::IFileSystem& Engine::GetFileSystem()
{
    return m_fileSystem;
}

Nuz::ILocalFile& Engine::GetLocalFile()
{
    return m_localFile;
}

Nuz::IEngine& Nuz::CreateGameDevice(const char* title,bool fullScreen,int w,int h){
    if(engine){
        throw std::runtime_error("Nuz::CreateGameDevice()::Engine already created.");
    }
    engine = new _Nuz::Engine;
    return *engine;
}

IEngine& GetGameDevice(){
    if(!engine){
        throw std::runtime_error("Nuz::GetGameDevice()::Engine has not created.");
    }
    return *engine;
}

void KillGameDevice(){
    if(!engine){
        throw std::runtime_error("Nuz::KillGameDevice()::Engine has not created.");
    }
    delete engine;
    engine = nullptr;
}
