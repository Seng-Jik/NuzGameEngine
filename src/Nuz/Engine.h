#pragma once
#include <memory>
#include "../../include/Nuz/Engine.h"

#include "FileSystem/FileSystem.h"
#include "FileSystem/LocalFile.h"


namespace _Nuz{

	class Engine:public Nuz::IEngine{
    private:
        _Nuz::FileSystem m_fileSystem;
        _Nuz::LocalFile m_localFile;
	public:
	    Engine(const char* title,bool fullScreen,int w,int h);
	    virtual ~Engine();
		virtual Nuz::ISceneManager& GetSceneManager(){};
		virtual Nuz::IFileSystem& GetFileSystem();
		virtual Nuz::IInputDeviceManager& GetInputDeviceManager(){};
		virtual Nuz::ILocalFile& GetLocalFile();
	};

}
