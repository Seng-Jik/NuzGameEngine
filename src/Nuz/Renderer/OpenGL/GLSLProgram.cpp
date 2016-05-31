#include "GLSLProgram.h"
#include "../../Engine.h"
using namespace std;
using namespace Nuz_;
using namespace Nuz_::Renderer;

GLSLProgram::GLSLProgram()
{
}


GLSLProgram::~GLSLProgram()
{
}

void Nuz_::Renderer::GLSLProgram::LoadShader(const Nuz::IShader::CreateConfig & c)
{
	//Compile Vertex Shader
	auto vert = glCreateShader(GL_VERTEX_SHADER);
	if (vert == 0) throw std::runtime_error("Can not create vertex shader.");
	auto buf = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(c.vertexShader);
	const char* charbuf = (char*)&(*buf)[0];
	glShaderSource(vert, 1, &charbuf, 0);
	glCompileShader(vert);

	GLint compileResult;
	glGetShaderiv(vert, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(vert, logLen, &written, log);
			string s(log);
			throw Nuz::IShader::ShaderCompileError("Vertex Shader:"+s);
			free(log);
		}
	}

	//Compile Fragment Shader
	auto frag = glCreateShader(GL_FRAGMENT_SHADER);
	if (frag == 0) throw std::runtime_error("Can not create fragment shader.");
	auto buf = Nuz::IEngine::GetGameDevice().GetFileSystem().LoadFile(c.fragmentShader);
	const char* charbuf = (char*)&(*buf)[0];
	glShaderSource(frag, 1, &charbuf, 0);
	glCompileShader(frag);

	GLint compileResult;
	glGetShaderiv(frag, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(frag, logLen, &written, log);
			string s(log);
			throw Nuz::IShader::ShaderCompileError("Fragment Shader:" + s);
			free(log);
		}
	}
	/*GLuint p = glCreateProgram();
	glAttachShader(p, v);
	glAttachShader(p, f);

	glLinkProgram(p);*/
}
