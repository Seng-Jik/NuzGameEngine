#pragma once
#include "../../../include/Nuz/SceneManager/SceneManager.h"
#include "../../../include/Nuz/Engine.h"
#include <memory>
#include <map>

namespace Nuz_ {
	class SceneManager final: public Nuz::ISceneManager
	{
	private:
		bool m_mainLoop;
		std::map < Nuz::IEngine::Message, std::function<void()>> m_messageProcessor;

		inline void sendMessage(Nuz::IEngine::Message m) const{
			if (m_messageProcessor.count(m))
				m_messageProcessor.at(m)();
		}
	public:
		SceneManager();
		~SceneManager();

		void Start(std::shared_ptr<Nuz::IScene>) override;	//Main Loop
		void FadeTo(std::shared_ptr<Nuz::IScene>, uint32_t time) override {};
		void Exit() override { m_mainLoop = false; };

		inline void BindMessageProcessor(Nuz::IEngine::Message m, std::function<void()> f) {
			m_messageProcessor[m] = f;
		}
		inline void UnbindMessageProcessor(Nuz::IEngine::Message m) {
			m_messageProcessor.erase(m);
		}
	};

}