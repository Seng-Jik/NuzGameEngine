#pragma once
#include "GameObjectFloder.h"
namespace Nuz_ {
	class Camera2D;
	class Camera3D;
	struct DrawTask{
		GameObjectFloder* gof;
		Camera2D* camera2D;
		Camera3D* camera3D;
		inline bool operator < (const DrawTask& d) const {
			return gof->GetDrawLevel() < d.gof->GetDrawLevel();
		}
	};
}