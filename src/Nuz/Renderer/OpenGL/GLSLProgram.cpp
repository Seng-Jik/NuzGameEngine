#include "GLSLProgram.h"
#include "../../Engine.h"
using namespace std;
using namespace Nuz_;
using namespace Nuz_::Renderer;

GLSLProgram::GLSLShader GLSLProgram::m_normalVertShader, GLSLProgram::m_normalFragShader;


GLSLProgram::GLSLProgram()
{
}


GLSLProgram::~GLSLProgram()
{
}

void Nuz_::Renderer::GLSLProgram::CompileNormalShaders()
{
	const char* vert =
		"#version 110\n"
		"uniform mat4 gl_ModelViewProjectionMatrix;\n"
		"attribute vec4 gl_Vertex;\n"
		"attribute vec4 gl_MultiTexCoord0;\n"
		"uniform mat4 gl_TextureMatrix[1];\n"
		"varying vec4 Nuz_texCoord;\n"
		"void main(){\n"
		"	gl_Position = gl_Vertex*gl_ModelViewProjectionMatrix;\n"
		"	Nuz_texCoord = gl_MultiTexCoord0 * gl_TextureMatrix[0];\n"
		"}\n";
	const char* frag =
		"#version 110\n"
		"varying vec4 Nuz_texCoord;\n"
		"uniform sampler2D Nuz_texture;\n"
		"void main(){\n"
		"	gl_FragColor = texture2D(Nuz_texture,Nuz_texCoord.st);\n"
		"}\n";
	m_normalFragShader.CompileShader(frag, GL_FRAGMENT_SHADER);
	m_normalVertShader.CompileShader(vert, GL_VERTEX_SHADER);
}



void Nuz_::Renderer::GLSLProgram::LoadShader(const Nuz::IShader::CreateConfig & c)
{
	Clear();
	m_program = glCreateProgram();
	if (m_program == 0) throw std::runtime_error("Can not create program object.");

	GLSLShader* vert = nullptr,*frag = nullptr;
	if (!c.vertexShader.empty()) {
		auto buf = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(c.vertexShader);
		vert = new GLSLShader;
		vert->CompileShader((char*)(*buf)[0], GL_VERTEX_SHADER);
	}
	else vert = &m_normalVertShader;
	if (!c.fragmentShader.empty()) {
		auto buf = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(c.fragmentShader);
		frag = new GLSLShader;
		frag->CompileShader((char*)(*buf)[0], GL_FRAGMENT_SHADER);
	}
	else frag = &m_normalFragShader;

	glAttachShader(m_program, *vert);
	glAttachShader(m_program, *frag);

	glLinkProgram(m_program);
	if (!c.fragmentShader.empty()) delete frag;
	if (!c.vertexShader.empty()) delete vert;
}

void Nuz_::Renderer::GLSLProgram::Clear()
{
	if(m_program) glDeleteProgram(m_program);
}

void Nuz_::Renderer::GLSLProgram::GLSLShader::CompileShader(const char * source, GLenum type)
{
	m_type = type;
	m_shader = glCreateShader(type);
	if (m_shader == 0) throw std::runtime_error("Can not create shader.");
	glShaderSource(m_shader, 1, &source, 0);
	glCompileShader(m_shader);

	GLint compileResult;
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(m_shader, logLen, &written, log);
			string s(log);
			free(log);
			throw Nuz::IShader::ShaderCompileError("Vertex Shader:" + s);
		}
	}
}

Nuz_::Renderer::GLSLProgram::GLSLShader::~GLSLShader()
{
	if(m_shader) glDeleteShader(m_shader);
}
