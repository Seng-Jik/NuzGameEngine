#pragma once
#include <memory>
#include <string>
#include <SDL.h>
#include "../../include/Nuz/Engine.h"

#include "SceneManager/SceneManager.h"
#include "FileSystem/FileSystem.h"
#include "FileSystem/LocalFile.h"


namespace Nuz_{

	class Engine:public Nuz::IEngine{
    private:
        Nuz_::FileSystem m_fileSystem;
        std::shared_ptr<Nuz_::LocalFile> m_localFile;
		Nuz_::SceneManager m_sceneManager;

		std::string m_windowTitle;
		SDL_Window* m_window = nullptr;
		SDL_GLContext m_glContext = nullptr;
	public:
	    Engine();
        ~Engine();
		Nuz::ISceneManager& GetSceneManager() override;;
		Nuz::IFileSystem& GetFileSystem() override;
        //Nuz::IInputDeviceManager& GetInputDeviceManager() override{};
        std::shared_ptr<Nuz::ILocalFile> GetLocalFile() override;
        void SetWindowTitle(const std::string&) noexcept override;
		void InitWindow(int w, int h, bool fullScreen) override;;
        void BindMessageProcessor(Message,std::function<void()>) override{};

		SDL_Window* GetWindow() { return m_window; }
		std::string GetWindowTitle() { return m_windowTitle; }
	};

}