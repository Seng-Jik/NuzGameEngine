#include "Engine.h"
#include <memory>
using namespace Nuz_;
using namespace Nuz;

static Nuz_::Engine engine;

Engine::Engine(){
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


IEngine& Nuz::GetGameDevice() noexcept{
    return engine;
}

