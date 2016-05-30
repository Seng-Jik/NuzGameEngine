#include "Particle2D.h"
#include "../../Engine.h"
#include <cmath>
#include <queue>
using namespace Nuz_;
using namespace Nuz;
using namespace std;


Particle2D::Particle2D()
{
}


Particle2D::~Particle2D()
{
}

void Nuz_::Particle2D::UseImage(const std::string & f, int num)
{
	m_dotTexture = ((Engine&)IEngine::GetGameDevice()).GetTextureLoader().LoadImage(f);
	auto rect = m_dotTexture->GetUVRect(num);

	drawDot.DefineBegin();
	glBegin(GL_QUADS); {
		glTexCoord2f(rect.x, rect.y + rect.h); glVertex2f(-1.0, -1.0);
		glTexCoord2f(rect.x + rect.w, rect.y + rect.h); glVertex2f(1.0, -1.0);
		glTexCoord2f(rect.x + rect.w, rect.y); glVertex2f(1.0, 1.0);
		glTexCoord2f(rect.x, rect.y); glVertex2f(-1.0, 1.0);
	}
	glEnd();
	drawDot.DefineEnd();
}

void Nuz_::Particle2D::BindSingle(std::function<void(Nuz::IParticle2D&, Nuz::IDot2D&)> f)
{
	single = f;
}


void Nuz_::Particle2D::AddDot(float x, float y,int num)
{
	for (int i = 0; i < num; ++i) {
		shared_ptr<Dot2D> p(new Dot2D(this));
		
		p->m_x = x;
		p->m_y = y;
		m_dots.insert(p);
	}
}

void Nuz_::Particle2D::Check()
{
	if (!single) throw std::runtime_error("Set single function please.");
	if (m_dotTexture->Empty()) throw std::runtime_error("Set image please.");
}

bool Nuz_::Particle2D::Empty()
{
	return m_dots.empty();
}

void Nuz_::Particle2D::Clear()
{
	m_dots.clear();
	m_frames = 0;
}

void Nuz_::Particle2D::OnDraw2D() const
{
	glMatrixPushEXT(GL_MODELVIEW);
	glMatrixLoadIdentityEXT(GL_MODELVIEW);
	m_dotTexture->Bind();
	for (auto& i : m_dots) {
		glMatrixPushEXT(GL_MODELVIEW);
		glColor4f(i->m_r, i->m_g, i->m_b, i->m_alpha);
		glMatrixTranslatefEXT(GL_MODELVIEW, i->m_x, i->m_y, 0);
		glMatrixScalefEXT(GL_MODELVIEW, i->m_size, i->m_size, 1);
		drawDot();
		glMatrixPopEXT(GL_MODELVIEW);
	}
	m_dotTexture->Unbind();
	glMatrixPopEXT(GL_MODELVIEW);
}

void Nuz_::Particle2D::OnUpdate(bool & draw2D, bool & draw3D)
{
	draw2D = true;
	queue<shared_ptr<Dot2D>> needKill;
	for (auto& i:m_dots) {
		single(*this, *i);
		i->m_x += i->m_speed*sin(i->m_angle);
		i->m_y += i->m_speed*cos(i->m_angle);
		if (i->m_size <= 0 || i->m_alpha <= 0)  needKill.push(i);
	}
	while (!needKill.empty()) {
		m_dots.erase(needKill.front());
		needKill.pop();
	}
	++m_frames;
}

void Nuz_::Dot2D::SetSpeed(float s)
{
	m_speed = s;
}

void Nuz_::Dot2D::AddSpeed(float s)
{
	m_speed += s;
}

float Nuz_::Dot2D::GetSpeed() const
{
	return m_speed;
}

void Nuz_::Dot2D::SetAlpha(float a)
{
	m_alpha = a;
}

void Nuz_::Dot2D::AddAlpha(float a)
{
	m_alpha += a;
}

float Nuz_::Dot2D::GetAlpha() const
{
	return m_alpha;
}

float Nuz_::Dot2D::GetAngle() const
{
	return m_angle;
}

void Nuz_::Dot2D::SetAngle(float a)
{
	m_angle = a;
}

void Nuz_::Dot2D::AddAngle(float a)
{
	m_angle += a;
}

void Nuz_::Dot2D::SetStatus(int n, float status)
{
	m_status[n] = status;
}

float Nuz_::Dot2D::GetStatus(int n) const
{
	return m_status[n];
}

void Nuz_::Dot2D::SetRGB(float r, float g, float b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}

void Nuz_::Dot2D::GetRGB(float & r, float & g, float & b) const
{
	r = m_r;
	g = m_g;
	b = m_b;
}

void Nuz_::Dot2D::AddRGB(float r, float g, float b)
{
	m_r += r;
	m_g += g;
	m_b += b;
}

void Nuz_::Dot2D::GetPos(float & x, float & y) const
{
	x = m_x;
	y = m_y;
}

void Nuz_::Dot2D::SetSize(float s)
{
	m_size = 2 * s;
}

float Nuz_::Dot2D::GetSize() const
{
	return m_size/2;
}

void Nuz_::Dot2D::AddSize(float s)
{
	m_size += 2 * s;
}

uint32_t Nuz_::Dot2D::GetLife() const
{
	return m_parent -> m_frames - m_birthday;
}

std::shared_ptr<IParticle2D> Nuz::IParticle2D::CreateParticle2D()
{
	return std::shared_ptr<IParticle2D>(new Nuz_::Particle2D);
}
