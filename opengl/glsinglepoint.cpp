#define GL_GLEXT_PROTOTYPES
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<cstdio>
static GLuint vao;
static GLuint program;

void print_log(GLuint object) 
{ 
    GLint log_length = 0; 
    if (glIsShader(object)) 
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length); 
    else if (glIsProgram(object)) 
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length); 
    else { 
        fprintf(stderr, "printlog: Not a shader or a program\n"); 
        return; 
    } 
       
    char* log = (char*)malloc(log_length); 
       
    if (glIsShader(object)) 
        glGetShaderInfoLog(object, log_length, NULL, log); 
    else if (glIsProgram(object)) 
        glGetProgramInfoLog(object, log_length, NULL, log); 
       
    fprintf(stderr, "%s", log); 
    free(log); 
}

void init()
{
    glPointSize(45);
    glEnable(GL_POINT_SMOOTH);
    static const char * vs_source[] =
        {
            "#version 120                                  \n"
            "                                              \n"
            "void main(void)                               \n"
            "{                                             \n"
            "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "                                                                  \n"
            "    gl_Position = vertices[gl_Vertex];                          \n"
            "    gl_PointSize = 40.0;                                          \n"
            "}                                             \n"
        };

    static const char * fs_source[] =
        {
            "#version 120                                  \n"
            "                                              \n"
            "vec4 color;                               \n"
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
    GLint compile_ok = GL_FALSE, link_ok = GL_FALSE; 
    glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok); 
    if (compile_ok == GL_FALSE) { 
        print_log(fs); 
        glDeleteShader(fs);
        fprintf(stderr,"fragment shader failed");
        return ; 
    } 
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, vs_source, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok); 
    if (compile_ok == GL_FALSE) { 
        print_log(vs); 
        glDeleteShader(vs); 
        return ; 
    } 
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok); 
    if (!link_ok) { 
        fprintf(stderr, "glLinkProgram:"); 
        print_log(program); 
    } 
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
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(40.0f);
    // glBegin(GL_POINTS);
    // glVertex4f(0.5, 0.5, -1.0, 1.0);
    // glVertex4f(0.0, 0.0, -1.0, 1.0);
    // glVertex4f( 0.25, -0.25, 0.5, 1.0);
    // glEnd();
    glDrawArrays(GL_POINTS, 0, 1);

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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);

    GLenum glew_status = glewInit(); 
    if (glew_status != GLEW_OK) 
    { 
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status)); 
        return EXIT_FAILURE; 
    }
    init();

    glutMainLoop();
    glDeleteProgram(program);
    glDeleteVertexArrays(1,&vao);
    return 0;
}
