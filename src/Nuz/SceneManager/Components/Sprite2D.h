#pragma once
#include "../../../../include/Nuz/SceneManager/Components/Sprite2D.h"
#include "../../Renderer/OpenGL/Texture.h"
#include "../../Renderer/OpenGL/CallList.h"
namespace Nuz_ {
	class Sprite2D final :public Nuz::ISprite2D
	{
	private:
		std::shared_ptr<Renderer::Texture> m_texture;
		int m_imageNum = 0;	//ͼ����
		struct FRect {
			GLfloat x, y, w=1.0f, h=1.0f;
		} m_dst;	//��Դλ�ú�Ŀ��λ��

		//GLfloat m_matrix[16];	//ģ�;���

		bool m_rotate = false;	//�Ƿ���ת
		float m_rotateAngle;	//��ת�Ƕ�
		float m_rotateX, m_rotateY;	//��ת����
		bool m_flipX, m_flipY;	//��ת

		bool m_visible = false;

		Renderer::CallList draw;	//����ͼ��
		void updateDrawCall(const FRect& src);	//����drawScreen����,src���ֱ����Կ�

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