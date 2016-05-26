#pragma once
#include "GameObjectFloder.h"
namespace Nuz_ {
	class Camera2D;
	class Camera3D;
	struct DrawTask2D {
		GameObjectFloder* gof;
		Camera2D* camera;
		inline bool operator < (const DrawTask2D& d) const {
			return gof->GetDrawLevel() < d.gof->GetDrawLevel();
		}
	};
	struct DrawTask3D {
		GameObjectFloder* gof;
		Camera3D* camera;
		inline bool operator < (const DrawTask3D& d) const {
			return gof->GetDrawLevel() < d.gof->GetDrawLevel();
		}
	};
}