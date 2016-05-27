#include "Camera2D.h"
#include <math.h>
#include "../../../include/Nuz/SceneManager/Camera2D.h"
using namespace Nuz_;


Camera2D::Camera2D()
{
	LoadIdentity();
}

void Nuz_::Camera2D::SetCamera(float left, float right, float top, float bottom)
{
	glMatrixPushEXT(GL_PROJECTION);
	glMatrixOrthoEXT(GL_PROJECTION, left, right, top, bottom, 0, 10000);
	glGetFloatv(GL_PROJECTION_MATRIX, m_matrix);
	glMatrixPopEXT(GL_PROJECTION);
	m_w = fabs(left - right);
	m_h = fabs(top - bottom);
}

void Nuz_::Camera2D::Zoom(float w, float h)
{
	glMatrixPushEXT(GL_PROJECTION);
	glMatrixLoadfEXT(GL_PROJECTION, m_matrix);
	glMatrixScalefEXT(GL_PROJECTION, w, h, 0);
	glGetFloatv(GL_PROJECTION_MATRIX, m_matrix);
	glMatrixPopEXT(GL_PROJECTION);
	m_w /= w;
	m_h /= h;
}

void Nuz_::Camera2D::Rotate(float angle)
{
	glMatrixPushEXT(GL_PROJECTION);
	glMatrixLoadfEXT(GL_PROJECTION, m_matrix);
	glMatrixRotatefEXT(GL_PROJECTION, angle, 0, 0, 1);
	glGetFloatv(GL_PROJECTION_MATRIX, m_matrix);
	glMatrixPopEXT(GL_PROJECTION);
}

void Nuz_::Camera2D::Move(float x, float y)
{
	glMatrixPushEXT(GL_PROJECTION);
	glMatrixLoadfEXT(GL_PROJECTION, m_matrix);
	glMatrixTranslatefEXT(GL_PROJECTION, x, y, 0);
	glGetFloatv(GL_PROJECTION_MATRIX, m_matrix);
	glMatrixPopEXT(GL_PROJECTION);
}

void Nuz_::Camera2D::UseMe() const
{
	glMatrixLoadfEXT(GL_PROJECTION, m_matrix);
}

void Nuz_::Camera2D::LoadIdentity()
{
	glMatrixPushEXT(GL_PROJECTION);
	glMatrixLoadIdentityEXT(GL_PROJECTION);
	glGetFloatv(GL_PROJECTION_MATRIX, m_matrix);
	glMatrixPopEXT(GL_PROJECTION);
	m_w = m_h = 2;
}

void Nuz_::Camera2D::GetScreenSize(float& w, float& h)
{
	w = m_w;
	h = m_h;
}

std::shared_ptr<Nuz::ICamera2D> Nuz::ICamera2D::CreateCamera2D()
{
	return std::shared_ptr<ICamera2D>(new Nuz_::Camera2D);
}
