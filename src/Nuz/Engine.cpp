#include "Engine.h"
#include <memory>
using namespace _Nuz;
using namespace Nuz;

_Nuz::Engine* engine = nullptr;

Engine::Engine(const char* title,bool fullScreen,int w,int h){
    //Todo:Init Libraries and Create Window Here
}

Engine::~Engine(){
    //Todo::Kill Libraries and Kill All Objects Here.
}

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
        throw CannotCreateEngine("Nuz::CreateGameDevice()::Engine already created.");
    }
    engine = new _Nuz::Engine(title,fullScreen,w,h);
    return *engine;
}

IEngine& Nuz::GetGameDevice(){
    if(!engine){
        throw HaveNotEngine("Nuz::GetGameDevice()::Engine has not created.");
    }
    return *engine;
}

void Nuz::KillGameDevice(){
    if(!engine){
        throw HaveNotEngine("Nuz::KillGameDevice()::Engine has not created.");
    }
    delete engine;
    engine = nullptr;
}
