#pragma once
#include "../../../include/Nuz/SceneManager/SceneManager.h"

namespace Nuz_ {
	class SceneManager : public Nuz::ISceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void Start(Nuz::IScene&) override {};
		void FadeTo(Nuz::IScene&, uint32_t time) override {};
		void Exit() override {};
	};

}