#include "Sprite2D.h"
#include "../../Renderer/OpenGL/Utils.h"
#include "../../Engine.h"
#include "../Camera2D.h"
#include "../../Font.h"
using namespace Nuz_;

Sprite2D::Sprite2D()
{
	//Renderer::LoadIdentityModelView44(m_matrix);
}

void Nuz_::Sprite2D::UseImage(const std::string & path, int num)
{
	//Renderer::LoadIdentityModelView44(m_matrix);
	m_texture = ((Nuz_::Engine&)Nuz::IEngine::GetGameDevice()).GetTextureLoader().LoadImage(path);
	m_imageNum = num;
	SetDstSizeAsDefault();
	m_visible = true;

	int iw = 0, ih = 0;
	m_texture->GetSize(iw, ih);
	auto uvRect = m_texture->GetUVRect(m_imageNum);
	SetSrc(0, 0, (int)(uvRect.w*iw), (int)(uvRect.h*ih));
}

void Nuz_::Sprite2D::UseText(Nuz::IFont& font, const std::wstring & text, uint8_t r,uint8_t g,uint8_t b)
{
	//Load Font
	SDL_Color fg = { r,g,b,255 };
	auto textSurface = TTF_RenderUNICODE_Blended((Nuz_::Font&)font, (Uint16*)text.c_str(), fg);
	if (!textSurface) throw std::runtime_error("Cannot render text to sprite.");

	m_texture = ((Nuz_::Engine&)Nuz::IEngine::GetGameDevice()).GetTextureLoader().RenderSurface(textSurface);
	SDL_FreeSurface(textSurface);
	m_imageNum = 0;
	SetDstSizeAsDefault();
	m_visible = true;

	int iw = 0, ih = 0;
	m_texture->GetSize(iw, ih);
	auto uvRect = m_texture->GetUVRect(m_imageNum);
	SetSrc(0, 0, (int)(uvRect.w*iw), (int)(uvRect.h*ih));
}

void Nuz_::Sprite2D::FreeImage()
{
	m_texture.reset();
	m_imageNum = 0;
	m_visible = false;
}

void Nuz_::Sprite2D::SetSrc(int x, int y, int w, int h)
{
	int iw=0, ih=0;
	m_texture->GetSize(iw, ih);
	float fw = (float)iw, fh = (float)ih;
	auto uvRect = m_texture->GetUVRect(m_imageNum);
	fw *= uvRect.w;
	fh *= uvRect.h;
	FRect fr;
	fr.x = float(x) / fw;
	fr.y = float(y) / fh;
	fr.w = float(w) / fw;
	fr.h = float(h) / fh;
	//updateDrawCall(fr);
	uvRect.x += fr.x;
	uvRect.y += fr.y;
	uvRect.w *= fr.w;
	uvRect.h *= fr.h;

	m_texCoord[0] = uvRect.x, m_texCoord[1] = uvRect.y + uvRect.h;
	m_texCoord[2] = uvRect.x + uvRect.w, m_texCoord[3] = uvRect.y + uvRect.h;
	m_texCoord[4] = uvRect.x + uvRect.w, m_texCoord[5] = uvRect.y;
	m_texCoord[6] = uvRect.x, m_texCoord[7] = uvRect.y;
}

void Nuz_::Sprite2D::GetSize(int & w, int & h) const
{
	m_texture->GetSize(w, h);
}

void Nuz_::Sprite2D::SetPos(float x, float y)
{
	m_dst.x = x;
	m_dst.y = y;
}

void Nuz_::Sprite2D::SetScale(float w, float h)
{
	m_dst.w = w;
	m_dst.h = h;
}

void Nuz_::Sprite2D::GetScale(float& w, float& h) {
	w = m_dst.w;
	h = m_dst.h;
}

void Nuz_::Sprite2D::SetAlpha(float a)
{
	m_a = a;
}

void Nuz_::Sprite2D::SetColorFliter(float r, float g, float b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}

void Nuz_::Sprite2D::SetDstSizeAsDefault()
{
	float w = 1, h = 1;
	if(GetCamera2D()) ((Camera2D*)GetCamera2D().get())->GetScreenSize(w, h);

	int winSizeW, winSizeH, imgSizeW, imgSizeH,texW,texH;
	((Nuz_::Engine*)(&Nuz::IEngine::GetGameDevice()))->GetWindowSize(winSizeW, winSizeH);
	auto imageRect = m_texture->GetUVRect(m_imageNum);
	m_texture->GetSize(texW, texH);

	imgSizeW = int(imageRect.w * texW);	//图像像素大小
	imgSizeH = int(imageRect.h * texH);

	m_dst.w = float(imgSizeW) / winSizeW / 2;	//图像占默认摄像机大小
	m_dst.h = float(imgSizeH) / winSizeH / 2;

	m_dst.w *= w;
	m_dst.h *= h;
}



//Sprite2D::~Sprite2D()
//{
//}

std::shared_ptr<Nuz::ISprite2D> Nuz::ISprite2D::CreateSprite2D()
{
	return std::shared_ptr<ISprite2D>(new Sprite2D);
}

void Nuz_::Sprite2D::SetRotate(bool enable, float x, float y, float angle, bool yFlip, bool xFlip)
{/*
	glMatrixPushEXT(GL_MODELVIEW);
	glMatrixLoadfEXT(GL_MODELVIEW, m_matrix);
	glMatrixTranslatefEXT(GL_MODELVIEW, x, y, 0);
	glMatrixRotatefEXT(GL_MODELVIEW, angle, 0, 0, 1);
	if(yFlip) glMatrixRotatefEXT(GL_MODELVIEW, 180, 0, 1, 0);
	if(xFlip) glMatrixRotatefEXT(GL_MODELVIEW, 180, 1, 0, 0);
	glMatrixTranslatefEXT(GL_MODELVIEW, -x, -y, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_matrix);
	glMatrixPopEXT(GL_MODELVIEW);*/
	m_rotate = enable;
	m_rotateX = x;
	m_rotateY = y;
	m_rotateAngle = angle;
	m_flipX = xFlip;
	m_flipY = yFlip;
}

void Nuz_::Sprite2D::SetVisible(bool b)
{
	m_visible = b;
}

void Nuz_::Sprite2D::OnUpdate(bool & draw2D, bool &) {
	draw2D = m_visible;
}

void Nuz_::Sprite2D::OnDraw2D() const
{
	glMatrixLoadIdentityEXT(GL_MODELVIEW);
	glMatrixTranslatefEXT(GL_MODELVIEW, m_dst.x, m_dst.y, 0);
	glMatrixScalefEXT(GL_MODELVIEW, m_dst.w, m_dst.h, 1);
	if (m_rotate) {
		if (m_flipY) {
			glMatrixRotatefEXT(GL_MODELVIEW, 180, 0, 1, 0);
			//glMatrixTranslatefEXT(GL_MODELVIEW, 1, 0, 0);
		}
		if (m_flipX) {
			glMatrixRotatefEXT(GL_MODELVIEW, 180, 1, 0, 0);
			//glMatrixTranslatefEXT(GL_MODELVIEW, 0, 1, 0);
		}
		glMatrixTranslatefEXT(GL_MODELVIEW, m_rotateX, m_rotateY, 0);
		glMatrixRotatefEXT(GL_MODELVIEW, m_rotateAngle, 0, 0, 1);
		glMatrixTranslatefEXT(GL_MODELVIEW, -m_rotateX, -m_rotateY, 0);
	}
	m_texture->Bind();
	glColor4f(m_r, m_g, m_b,m_a);

	glBegin(GL_QUADS); {
		glMultiTexCoord2f(GL_TEXTURE0, m_texCoord[0], m_texCoord[1]); glVertex2f(-1.0, -1.0);
		glMultiTexCoord2f(GL_TEXTURE0, m_texCoord[2], m_texCoord[3]); glVertex2f(1.0, -1.0);
		glMultiTexCoord2f(GL_TEXTURE0, m_texCoord[4], m_texCoord[5]); glVertex2f(1.0, 1.0);
		glMultiTexCoord2f(GL_TEXTURE0, m_texCoord[6], m_texCoord[7]); glVertex2f(-1.0, 1.0);
	}
	glEnd();
	//auto imageRect = m_texture->GetUVRect(0);

	m_texture->Unbind();
}
