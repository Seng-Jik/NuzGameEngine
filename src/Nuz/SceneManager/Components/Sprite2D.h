#pragma once
#include "../../../../include/Nuz/SceneManager/Components/Sprite2D.h"
#include "../../Renderer/OpenGL/Texture.h"
#include "../../Renderer/OpenGL/CallList.h"
namespace Nuz_ {
	class Sprite2D final :public Nuz::ISprite2D
	{
	private:
		std::shared_ptr<Renderer::Texture> m_texture;
		int m_imageNum = 0;	//图像编号
		struct FRect {
			GLfloat x, y, w=1.0f, h=1.0f;
		} m_dst;	//来源位置和目标位置

		//GLfloat m_matrix[16];	//模型矩阵

		bool m_rotate = false;	//是否旋转
		float m_rotateAngle;	//旋转角度
		float m_rotateX, m_rotateY;	//旋转中心
		bool m_flipX, m_flipY;	//翻转

		bool m_visible = false;

		Renderer::CallList draw;	//绘制图像
		void updateDrawCall(const FRect& src);	//更新drawScreen函数,src部分编入显卡

	public:
		Sprite2D();
		void UseImage(const std::string& path, int num = 0) override;
		void UseText(Nuz::IFont& font, const std::wstring& text, int size = 32, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255) override;
		void FreeImage() override;
		void SetSrc(int x, int y, int w, int h) override;
		void GetSize(int& w, int& h) const override;
		void SetPos(float x, float y) override;
		void SetScale(float w, float h) override;
		void SetDstSizeAsDefault() override;
		void SetRotate(bool enable, float x = 0, float y = 0, float angle = 180, bool yFlip = false, bool xFlip = false) override;
		void SetVisible(bool) override;
		void GetScale(float& w, float& h) override;
		
		void OnUpdate(bool& draw2D, bool&) override;
		void OnDraw2D() const override;
	};

}