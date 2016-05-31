#pragma once
#include "../../../../include/Nuz/SceneManager/Components/Particle2D.h"
#include "../../Renderer/OpenGL/Texture.h"
#include "../../Renderer/OpenGL/CallList.h"
#include <memory>
#include <set>
#include <list>
#include <cstdint>
namespace Nuz_ {
	struct Dot2D;
	class Particle2D :public Nuz::IParticle2D
	{
	friend struct Dot2D;
	private:
		std::multiset<std::shared_ptr<Dot2D>> m_dots;
		//std::list<Dot2D> m_dots;
		std::shared_ptr<Renderer::Texture> m_dotTexture;	//��������
		std::function<void(Nuz::IParticle2D&, Nuz::IParticle2D::Dot2D&)> single,initer;

		Renderer::CallList drawDot;
	public:
		Particle2D();
		~Particle2D();
		void UseImage(const std::string&, int num) override;
		void BindSingle(std::function<void(Nuz::IParticle2D&, Nuz::IParticle2D::Dot2D&)>) override;
		void BindIniter(std::function<void(Nuz::IParticle2D&, Nuz::IParticle2D::Dot2D&)>) override;
		void AddDot(float x,float y,int num) override;
		void Check() override;
		bool Empty() override;
		void Clear() override;

		//���ʵ��
		void OnDraw2D() const override;	//�������Ҫ����2D���ʱִ��
		void OnUpdate(bool& draw2D, bool& draw3D) override;
	};
}

