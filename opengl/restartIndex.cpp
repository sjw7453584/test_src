#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cstdio>
#define BUFFER_OFFSET(offset) ((GLvoid *) NULL + offset)
#define XStart  -0.8
#define XEnd     0.8
#define YStart   -0.8
#define YEnd     0.8
#define NumXPoints 6
#define NumYPoints 6
#define NumPoints (NumXPoints * NumYPoints)
#define NumPointsPerStrip (NumXPoints)
#define NumStrips (NumYPoints-1)
#define RestartIndex 0xffff

void init()
{
    GLuint vbo, ebo;
    GLfloat*vertices;
    GLushort *indices;
    /* Set up vertex data */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2*NumPoints*sizeof(GLfloat),
                 NULL, GL_STATIC_DRAW);
    vertices = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (vertices == NULL) {
        fprintf(stderr, "Unable to map vertex buffer\n");
        exit(EXIT_FAILURE);
    }
    else {
        int i, j;
        GLfloat dx = (XEnd - XStart) / (NumXPoints - 1);
        GLfloat dy = (YEnd - YStart) / (NumYPoints - 1);
        GLfloat *tmp = vertices;
        int n = 0;
        for (j = 0; j < NumYPoints; ++j) {
            GLfloat y = YStart + j*dy;
            for (i = 0; i < NumXPoints; ++i) {
                GLfloat x = XStart + i*dx;
                *tmp++ = x;
                *tmp++ = y;
            }
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glVertexPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);
    }
    /* Set up index data */
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    /* We allocate an extra restart index because it simplifies
    **
    the element-array loop logic */
    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                  NumStrips*(NumPointsPerStrip + 1)*sizeof(GLushort),
                  NULL, GL_STATIC_DRAW );
    indices = (GLushort*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_WRITE_ONLY);
    if (indices == NULL) {
        fprintf(stderr, "Unable to map index buffer\n");
        exit(EXIT_FAILURE);
    }
    else {
        int i, j;
        GLushort *index = indices;
        for (j = 0; j < NumStrips; ++j) {
            GLushort bottomRow = j*NumYPoints;
            GLushort topRow = bottomRow + NumYPoints;
            for (i = 0; i < NumXPoints; ++i) {
                *index++ = topRow + i;
                *index++ = bottomRow + i;
            }
            *index++ = RestartIndex;
        }
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }
    glPrimitiveRestartIndex(RestartIndex);
    glEnable(GL_PRIMITIVE_RESTART);
}
void display()
{
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    int i, start;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 1, 0);
    glDrawElements(GL_TRIANGLE_STRIP,
                   NumStrips*(NumPointsPerStrip + 1 ),
                   GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

    
    // glDrawElements(GL_TRIANGLE_STRIP,
    //                3,
    //                GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
    glutSwapBuffers();
}
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 150);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    // glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
