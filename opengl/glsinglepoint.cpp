#define GL_GLEXT_PROTOTYPES
#include<GL/freeglut.h>
static GLuint vao;
static GLuint program;
void init()
{
    glPointSize(5);
    glEnable(GL_POINT_SMOOTH);
    static const char * vs_source[] =
        {
            "#version 430 core                             \n"
            "                                              \n"
            "void main(void)                               \n"
            "{                                             \n"
            "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "                                                                  \n"
            "    gl_Position = vertices[gl_VertexID];                          \n"
            "    gl_PointSize = 40.0"
            "}                                             \n"
        };

    static const char * fs_source[] =
        {
            "#version 430 core                             \n"
            "                                              \n"
            "out vec4 color;                               \n"
            "                                              \n"
            "void main(void)                               \n"
            "{                                             \n"
            "    color = vec4(0.0, 0.8, 1.0, 1.0);         \n"
            "}                                             \n"
        };

    program = glCreateProgram();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, fs_source, NULL);
    glCompileShader(fs);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, vs_source, NULL);
    glCompileShader(vs);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

}
void keyboard(unsigned char key, int x, int y) {

}

void display(void)
{
    static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, red);

    glUseProgram(program);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(40.0f);
    // glBegin(GL_POINTS);
    // glVertex4f(0.5, 0.5, -1.0, 1.0);
    // glVertex4f(0.0, 0.0, -1.0, 1.0);
    // glVertex4f( 0.25, -0.25, 0.5, 1.0);
    // glEnd();
    glDrawArrays(GL_LINES, 0, 2);

    glFlush();
}

void reshape(int w, int h)
{
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
if (w <= h)
glOrtho(-2.5, 2.5, -2.5*(GLfloat)h/(GLfloat)w,
2.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
else
glOrtho(-2.5*(GLfloat)w/(GLfloat)h,
2.5*(GLfloat)w/(GLfloat)h, -2.5, 2.5, -10.0, 10.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
 // gluLookAt(0, 0, -10.0, 0, 0, 0, 0, 1, 0);
}
 int main(int argc, char** argv)
{
init();
    glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(500, 500);
glutCreateWindow(argv[0]);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
glutDisplayFunc(display);
glutMainLoop();
 glDeleteProgram(program);
 glDeleteVertexArrays(1,&vao);
return 0;
}
