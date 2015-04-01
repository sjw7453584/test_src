#include <cstdio>
#include <GL/gl.h>
int main ()
{
    glClearColor(0.0,0.0,0.0,0.0);
    const GLubyte* version = glGetString(GL_VERSION);
    return 0;
}
