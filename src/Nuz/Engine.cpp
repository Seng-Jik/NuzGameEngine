#include "Engine.h"
#include <memory>
using namespace Nuz_;
using namespace Nuz;

Engine::Engine():m_localFile(new Nuz_::LocalFile){
	SDL_Init(SDL_INIT_EVERYTHING);

}

Engine::~Engine(){
	SDL_DestroyWindow(m_window);
	SDL_GL_DeleteContext(m_glContext);
	SDL_Quit();
}

Nuz::ISceneManager & Nuz_::Engine::GetSceneManager() {
	return m_sceneManager;
}

void Nuz_::Engine::SetWindowTitle(const std::string& s) noexcept {
	if (m_window) SDL_SetWindowTitle(m_window,s.c_str());
	m_windowTitle = s;
}

Nuz::IFileSystem & Nuz_::Engine::GetFileSystem()
{
	return m_fileSystem;
}

std::shared_ptr<Nuz::ILocalFile> Engine::GetLocalFile()
{
    return m_localFile;
}

void Nuz_::Engine::InitWindow(int w, int h, bool fullScreen) {
	if (m_window || m_glContext) throw std::runtime_error("Window have already created.");
	if (fullScreen) {
		if(w == 1)
			m_window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN_DESKTOP);
		else
			m_window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
	}else
		m_window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
	
	m_glContext = SDL_GL_CreateContext(m_window);
	if (!m_window || !m_glContext) throw std::runtime_error(std::string("SDL Error:") + SDL_GetError());
}


IEngine& Nuz::IEngine::GetGameDevice() noexcept{
    static Nuz_::Engine engine;
    return engine;
}
