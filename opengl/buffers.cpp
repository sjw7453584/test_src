#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <cstdio>
#define BUFFER_OFFSET(offset) ((GLvoid *) NULL + offset)
#define VERTICES 0
#define INDICES 1
#define NUM_BUFFERS 2

void init(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}
void display(){
    glClearColor(1.0, 1.0, 0.0, 1.0 );
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0 );
    glViewport(0, 0, (GLsizei) 400, (GLsizei) 800);

    GLuint buffers[NUM_BUFFERS];

    GLfloat vertices[][2] = {
        { -0.5, -0.5 },
        { 0.5, -0.5 },
        { 0.5, 0.5, },
        { -0.5, 0.5 },
        { 0.4, 0.9 },
        { 0.4, 0.8 },
        { 0.8 ,0.8 },
        { 0.8, 0.9 }
    };
    GLubyte indices[][4] = {
        { 0, 1, 2, 3 },
        { 4, 7, 6, 5 },
        { 0, 4, 5, 1 },
        { 3, 2, 6, 7 },
        { 0, 3, 7, 4 },
        { 1, 5, 6, 2 }
    };
    glGenBuffers(NUM_BUFFERS, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);
    glVertexPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(0));
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDICES]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

    glDrawElements(GL_QUADS, 8, GL_UNSIGNED_BYTE,
                   BUFFER_OFFSET(0));
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE,
                   BUFFER_OFFSET(0));
    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 800);
    glutInitWindowPosition(200, 300);
    glutCreateWindow(argv[0]);
    init(400,150);
    // display();
    glutDisplayFunc(display);
    // glutReshapeFunc(reshape);
    // glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

