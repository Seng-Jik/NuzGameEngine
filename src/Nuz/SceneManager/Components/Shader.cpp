#include "Shader.h"
#include "../../Renderer/OpenGL/Shader.h"
#include "../../../../include/Nuz/SceneManager/Components/Shader.h"
using namespace Nuz;
using namespace Nuz_;
using namespace Nuz_::Renderer;
using namespace std;


Shader::Shader()
{
}


Shader::~Shader()
{
	Clear();
}

void Nuz_::Renderer::Shader::LoadShader(const char * vert, const char * frag)
{
}

void Nuz_::Renderer::Shader::Clear()
{

}

