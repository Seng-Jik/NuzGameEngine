#pragma once
#include "../Renderer/OpenGL/glew.h"
#include "../../../include/Nuz/SceneManager/Camera2D.h"

namespace Nuz_ {
	class Camera2D final:public Nuz::ICamera2D
	{
	private:
		GLfloat m_matrix[16];
		float m_w, m_h;
	public:
		Camera2D();
		void SetCamera(float left, float right, float top, float bottom) override;
		void Zoom(float w, float h) override;
		void Rotate(float angle) override;
		void Move(float x, float y) override;
		void UseMe() const;
		void LoadIdentity();
		void GetScreenSize(float& w,float& h);
	};
}