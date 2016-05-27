#include "Utils.h"

void Nuz_::Renderer::LoadIdentityModelView44(GLfloat* m)
{
	glMatrixPushEXT(GL_MODELVIEW);
	glMatrixLoadIdentityEXT(GL_MODELVIEW);
	glGetFloatv(GL_PROJECTION_MATRIX, m);
	glMatrixPopEXT(GL_MODELVIEW);
}
