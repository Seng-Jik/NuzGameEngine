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
		std::shared_ptr<Renderer::Texture> m_dotTexture;	//粒子纹理
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

		//组件实现
		void OnDraw2D() const override;	//当组件需要绘制2D物件时执行
		void OnUpdate(bool& draw2D, bool& draw3D) override;
	};
}

