#pragma once
#include <memory>
#include "../../include/Nuz/Engine.h"

#include "FileSystem/FileSystem.h"
#include "FileSystem/LocalFile.h"


namespace Nuz_{

	class Engine:public Nuz::IEngine{
    private:
        Nuz_::FileSystem m_fileSystem;
        Nuz_::LocalFile m_localFile;
	public:
	    Engine();
	    virtual ~Engine();
		virtual Nuz::ISceneManager& GetSceneManager(){};
		virtual Nuz::IFileSystem& GetFileSystem();
		virtual Nuz::IInputDeviceManager& GetInputDeviceManager(){};
		virtual Nuz::ILocalFile& GetLocalFile();
		virtual void SetWindowTitle(const std::string&) noexcept {};
		virtual void InitWindow(int w,int h,bool fullScreen){};
	};

}
