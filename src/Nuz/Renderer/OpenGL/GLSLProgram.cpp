#include "GLSLProgram.h"
#include "../../Engine.h"
using namespace std;
using namespace Nuz_;
using namespace Nuz_::Renderer;

GLSLProgram::GLSLShader GLSLProgram::m_normalVertShader;
GLuint GLSLProgram::m_normalShaderProgram = 0;


GLSLProgram::GLSLProgram()
{
}


GLSLProgram::~GLSLProgram()
{
	Clear();
}

void Nuz_::Renderer::GLSLProgram::CompileNormalShaders()
{
	m_normalShaderProgram = glCreateProgram();
	const char* vert =
		"#version 110\n"
		"attribute vec4 gl_MultiTexCoord0;"
		"uniform mat4 gl_TextureMatrix[1];"
		"varying vec4 Nuz_texCoord;"
		"attribute vec4 gl_Color;"
		"varying vec4 Nuz_Color;"
		"void main(){"
		"	Nuz_texCoord = gl_MultiTexCoord0 * gl_TextureMatrix[0];"
		"	Nuz_Color = gl_Color;"
		"	gl_Position = ftransform();"
		"}";
	const char* vert2 =
		"#version 110\n"
		"void main(){"
		"	gl_Position = ftransform();"
		"}";
	const char* frag =
		"#version 110\n"
		"varying vec4 Nuz_Color;"
		"varying vec4 Nuz_texCoord;"
		"uniform sampler2D Nuz_texture;"
		"void main(){\n"
		"	gl_FragColor = texture2D(Nuz_texture,Nuz_texCoord.st);"
		"	gl_FragColor = gl_FragColor * Nuz_Color;"
		"	gl_FragColor[3] = Nuz_Color[3];"
		"}";
	GLSLShader normalFragShader;
	normalFragShader.CompileShader(frag, GL_FRAGMENT_SHADER);
	m_normalVertShader.CompileShader(vert, GL_VERTEX_SHADER);

	glAttachShader(m_normalShaderProgram, normalFragShader);
	glAttachShader(m_normalShaderProgram, m_normalVertShader);
	glLinkProgram(m_normalShaderProgram);
	m_normalVertShader.CompileShader(vert2, GL_VERTEX_SHADER);
	glUseProgram(m_normalShaderProgram);

	auto pTex = glGetUniformLocation(m_normalShaderProgram, "Nuz_texture");
	glProgramUniform1iEXT(m_normalShaderProgram, pTex, 0);
}

void Nuz_::Renderer::GLSLProgram::DestroyNormalShaders()
{
	if(m_normalShaderProgram) glDeleteProgram(m_normalShaderProgram);
}



void Nuz_::Renderer::GLSLProgram::LoadShader(const Nuz::IShader::CreateConfig & c)
{
	Clear();
	m_program = glCreateProgram();
	if (m_program == 0) throw std::runtime_error("Can not create program object.");

	GLSLShader* vert = nullptr,*frag = nullptr;
	if (!c.vertexShader.empty()) {
		auto buf = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(c.vertexShader);
		buf->push_back('\0');
		vert = new GLSLShader;
		vert->CompileShader((char*)&(*buf)[0], GL_VERTEX_SHADER);
	}
	else vert = &m_normalVertShader;
	if (!c.fragmentShader.empty()) {
		auto buf = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(c.fragmentShader);
		buf->push_back('\0');
		frag = new GLSLShader;
		frag->CompileShader((char*)&(*buf)[0], GL_FRAGMENT_SHADER);
	}
	else throw std::runtime_error("You must use a fragment shader.");

	glAttachShader(m_program, *vert);
	glAttachShader(m_program, *frag);

	glLinkProgram(m_program);
	delete frag;
}

void Nuz_::Renderer::GLSLProgram::Clear()
{
	if(m_program) glDeleteProgram(m_program);
	m_program = 0;
}

void Nuz_::Renderer::GLSLProgram::GLSLShader::CompileShader(const char * source, GLenum type)
{
	Clear();
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
			throw Nuz::IShader::ShaderCompileError("Shader Compile Failed:\n" + s);
		}
	}
}

void Nuz_::Renderer::GLSLProgram::GLSLShader::Clear()
{
	if (m_shader) glDeleteShader(m_shader);
}

Nuz_::Renderer::GLSLProgram::GLSLShader::~GLSLShader()
{
	Clear();
}
