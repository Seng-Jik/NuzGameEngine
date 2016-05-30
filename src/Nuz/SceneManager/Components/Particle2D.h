#pragma once
#include "../../../../include/Nuz/SceneManager/Components/Particle2D.h"
#include "../../Renderer/OpenGL/Texture.h"
#include "../../Renderer/OpenGL/CallList.h"
#include <memory>
#include <set>
#include <cstdint>
namespace Nuz_ {
	class Dot2D;
	class Particle2D :public Nuz::IParticle2D
	{
	friend class Dot2D;
	private:
		std::multiset<std::shared_ptr<Dot2D>> m_dots;
		uint32_t m_frames = 0;	//生命长度
		std::shared_ptr<Renderer::Texture> m_dotTexture;	//粒子纹理
		std::function<void(Nuz::IParticle2D&, Nuz::IDot2D&)> single;

		Renderer::CallList drawDot;
	public:
		Particle2D();
		~Particle2D();
		void UseImage(const std::string&, int num) override;
		void BindSingle(std::function<void(Nuz::IParticle2D&, Nuz::IDot2D&)>) override;
		void AddDot(float x,float y,int num) override;
		void Check() override;
		bool Empty() override;
		void Clear() override;

		//组件实现
		void OnDraw2D() const override;	//当组件需要绘制2D物件时执行
		void OnUpdate(bool& draw2D, bool& draw3D) override;
	};

	class Dot2D:public Nuz::IDot2D {
	friend class Particle2D;
	private:
		float m_speed = 0.0f, m_alpha = 1.0f, m_angle = 0.0f, m_status[4] = { 0.0f },
			m_r = 1.0f, m_g = 1.0f, m_b = 1.0f, m_x = 0.0, m_y = 0.0, m_size = 2.0f;
		uint32_t m_birthday = 0;	//生命起始点
		Nuz_::Particle2D* m_parent;
	public:
		inline Dot2D(Nuz_::Particle2D* s) :m_parent(s) {};
		void SetSpeed(float s) override;
		void AddSpeed(float s) override;
		float GetSpeed() const override;
		void SetAlpha(float a) override;
		void AddAlpha(float a) override;
		float GetAlpha() const override;
		float GetAngle() const override;
		void SetAngle(float a) override;
		void AddAngle(float a) override;
		void SetStatus(int n, float status) override;
		float GetStatus(int n) const override;
		void SetRGB(float r, float g, float b) override;
		void GetRGB(float& r, float& g, float& b) const override;
		void AddRGB(float r, float g, float b) override;
		void GetPos(float& x, float& y) const override;
		void SetSize(float) override;
		float GetSize() const override;
		void AddSize(float) override;
		uint32_t GetLife() const override;
		inline bool operator < (const Dot2D& b) const {
			return m_x < b.m_x;
		}
	};
}

