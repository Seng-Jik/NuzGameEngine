#include "Engine.h"
#include <memory>
using namespace Nuz_;
using namespace Nuz;

Engine::Engine():m_localFile(new Nuz_::LocalFile){
    //Todo:Init Libraries

}

Engine::~Engine(){
    //Todo::Kill Libraries and Kill All Objects Here.
}

Nuz::IFileSystem& Engine::GetFileSystem()
{
    return m_fileSystem;
}

std::shared_ptr<Nuz::ILocalFile> Engine::GetLocalFile()
{
    return m_localFile;
}


IEngine& Nuz::GetGameDevice() noexcept{
    static Nuz_::Engine engine;
    return engine;
}

