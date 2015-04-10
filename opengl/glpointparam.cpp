#define GL_GLEXT_PROTOTYPES
#include<GL/freeglut.h>

static GLfloat constant[3] = {1.0, 0.0, 0.0};
static GLfloat linear[3] = {0.0, 0.12, 0.0};
static GLfloat quadratic[3] = {0.0, 0.0, 0.01};
void init()
{
    glPointSize(5);
    glEnable(GL_POINT_SMOOTH);
}
void keyboard(unsigned char key, int x, int y) {
switch (key) {
case 'c':
glPointParameterfv (GL_POINT_DISTANCE_ATTENUATION, constant);
glutPostRedisplay();
break;
case 'l':
glPointParameterfv (GL_POINT_DISTANCE_ATTENUATION, linear);
glutPostRedisplay();
break;
case 'q':
glPointParameterfv (GL_POINT_DISTANCE_ATTENUATION, quadratic);
glutPostRedisplay();
break;
case 'b':
glMatrixMode (GL_MODELVIEW);
glTranslatef (0.0, 0.0, -0.5);
glutPostRedisplay();
break;
case 'f':
glMatrixMode (GL_MODELVIEW);
glTranslatef (0.0, 0.0, 0.5);
glutPostRedisplay();
 break;
 }
}

void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0f, 0.75f, 0.0f);
 glBegin(GL_POINTS) ;
// glFogCoordf(f1);
glVertex3f(2.0f, -2.0f, 1.0f);
// glFogCoordf(f2);
glVertex3f(-2.0f, 0.0f, -2.0f);
// glFogCoordf(f3);
glVertex3f(0.0f, 2.0f, -3.0f);
glEnd();
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
}
 int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(500, 500);
glutCreateWindow(argv[0]);
init();
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
glutDisplayFunc(display);
glutMainLoop();
return 0;
}

