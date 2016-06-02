#include "Shader.h"
#include "../../../../include/Nuz/SceneManager/Components/Shader.h"
using namespace Nuz;
using namespace Nuz_;
using namespace Nuz_::Renderer;
using namespace std;

std::map<Nuz::IShader::CreateConfig, std::weak_ptr<Nuz_::Renderer::GLSLProgram>, Shader::CreateConfigCompare> Shader::m_shaderCache;

Nuz_::Shader::Shader(const Nuz::IShader::CreateConfig & c)
{
	if (m_shaderCache.count(c)) {
		if (!m_shaderCache.at(c).expired()) {
			m_shader = m_shaderCache.at(c).lock();
		}
	}
	m_shader = shared_ptr<Nuz_::Renderer::GLSLProgram> (new Renderer::GLSLProgram);
	m_shader->LoadShader(c);
	m_shaderCache[c] = m_shader;
}

void Nuz_::Shader::SetUniformFloat(const std::string & uniform, int size, float i1, float i2, float i3, float i4)
{
	m_uniformsf[uniform].size = size;
	auto& p = m_uniformsf[uniform];
	if (size >= 1) p.var[0] = i1;
	if (size >= 2) p.var[1] = i2;
	if (size >= 3) p.var[2] = i3;
	if (size >= 4) p.var[3] = i4;
}

void Nuz_::Shader::SetUniformInt(const std::string & uniform, int size, int i1, int i2, int i3, int i4)
{
	m_uniformsi[uniform].size = size;
	auto& p = m_uniformsi[uniform];
	if (size >= 1) p.var[0] = i1;
	if (size >= 2) p.var[1] = i2;
	if (size >= 3) p.var[2] = i3;
	if (size >= 4) p.var[3] = i4;
}

Nuz::IShader::ShaderHandle Nuz_::Shader::GetHandle()
{
	return *m_shader;
}

void Nuz_::Shader::OnDraw2DReady() const
{
	for (auto & p : m_uniformsi) {
		auto pLoc = glGetUniformLocation(*m_shader,p.first.c_str());
		switch (p.second.size) {
		case 1:
			glProgramUniform1iEXT(*m_shader, pLoc,p.second.var[0]);
			break;
		case 2:
			glProgramUniform2iEXT(*m_shader, pLoc, p.second.var[0], p.second.var[1]);
			break;
		case 3:
			glProgramUniform3iEXT(*m_shader, pLoc, p.second.var[0], p.second.var[1], p.second.var[2]);
			break;
		case 4:
			glProgramUniform4iEXT(*m_shader, pLoc, p.second.var[0], p.second.var[1], p.second.var[2], p.second.var[3]);
			break;
		default:
			throw std::runtime_error("Invaild uniform var size.");
		}
	}
	for (auto & p : m_uniformsf) {
		auto pLoc = glGetUniformLocation(*m_shader, p.first.c_str());
		switch (p.second.size) {
		case 1:
			glProgramUniform1fEXT(*m_shader, pLoc, p.second.var[0]);
			break;
		case 2:
			glProgramUniform2fEXT(*m_shader, pLoc, p.second.var[0], p.second.var[1]);
			break;
		case 3:
			glProgramUniform3fEXT(*m_shader, pLoc, p.second.var[0], p.second.var[1], p.second.var[2]);
			break;
		case 4:
			glProgramUniform4fEXT(*m_shader, pLoc, p.second.var[0], p.second.var[1], p.second.var[2], p.second.var[3]);
			break;
		default:
			throw std::runtime_error("Invaild uniform var size.");
		}
	}
	m_shader->Use();
}

void Nuz_::Shader::OnDraw2DFinished() const
{
	m_shader->Unuse();
}

void Nuz_::Shader::OnDraw3DReady() const
{
	OnDraw2DReady();
}

void Nuz_::Shader::OnDraw3DFinished() const
{
	OnDraw2DFinished();
}

std::shared_ptr<IShader> Nuz::IShader::CreateShaderFromFile(const CreateConfig &c)
{
	return std::shared_ptr<IShader>(new Nuz_::Shader(c));
}
