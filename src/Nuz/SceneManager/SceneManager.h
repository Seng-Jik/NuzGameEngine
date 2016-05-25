#pragma once
#include "../../../include/Nuz/SceneManager/SceneManager.h"
#include <memory>

namespace Nuz_ {
	class SceneManager final: public Nuz::ISceneManager
	{
	private:
		bool m_mainLoop;
	public:
		SceneManager();
		~SceneManager();

		void Start(std::shared_ptr<Nuz::IScene>) override;	//Main Loop
		void FadeTo(std::shared_ptr<Nuz::IScene>, uint32_t time) override {};
		void Exit() override { m_mainLoop = false; };
	};

}