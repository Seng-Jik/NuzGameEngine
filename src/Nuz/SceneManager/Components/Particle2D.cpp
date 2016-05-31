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

void Nuz_::Particle2D::BindSingle(std::function<void(Nuz::IParticle2D&, Nuz::IParticle2D::Dot2D&)> f)
{
	single = f;
}

void Nuz_::Particle2D::BindIniter(std::function<void(Nuz::IParticle2D&, Nuz::IParticle2D::Dot2D&)> f)
{
	initer = f;
}


void Nuz_::Particle2D::AddDot(float x, float y,int num)
{
	for (int i = 0; i < num; ++i) {
		Dot2D p;
		p.x = x;
		p.y = y;
		if (initer) initer(*this,p);
		m_dots.push_back(p);
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
}

void Nuz_::Particle2D::OnDraw2D() const
{
	glMatrixPushEXT(GL_MODELVIEW);
	m_dotTexture->Bind();
	for (auto& i : m_dots) {
		glMatrixLoadIdentityEXT(GL_MODELVIEW);
		glColor4f(i.r, i.g, i.b, i.alpha);
		glMatrixTranslatefEXT(GL_MODELVIEW, i.x, i.y, 0);
		glMatrixScalefEXT(GL_MODELVIEW, i.size, i.size, 1);
		drawDot();
	}
	m_dotTexture->Unbind();
	glMatrixPopEXT(GL_MODELVIEW);
}

void Nuz_::Particle2D::OnUpdate(bool & draw2D, bool & draw3D)
{
	draw2D = true;
	for (auto i = m_dots.begin(); i != m_dots.end();++i) {
		single(*this, *i);
		i->x += i->speed*sin(i->angle);
		i->y += i->speed*cos(i->angle);
	}
	auto nend = remove_if(m_dots.begin(), m_dots.end(), [](const auto& i) {
		return i.alpha <= 0 || i.size <= 0;
	});
	m_dots.erase(nend, m_dots.end());
}

std::shared_ptr<IParticle2D> Nuz::IParticle2D::CreateParticle2D()
{
	return std::shared_ptr<IParticle2D>(new Nuz_::Particle2D);
}
