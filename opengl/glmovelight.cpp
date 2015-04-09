#include<GL/freeglut.h>
static int spin = 0;
void init(void)
{
glClearColor(0.0, 0.0, 0.0, 0.0);
glShadeModel(GL_SMOOTH);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_DEPTH_TEST);
 GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
 glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);
}
/* Here is where the light position is reset after the modeling
* transformation (glRotated) is called. This places the
* light at a new position in world coordinates. The cube
* represents the position of the light.
*/
void display(void)
{
GLfloat position[] = { 0.0, 0.0, 1.0, 1.0 };
// GLfloat position[] = { 1.0, 1.0, 1.0, 0.0 };
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPushMatrix();
glLightfv(GL_LIGHT0, GL_POSITION, position);
 glTranslatef(1.0, 0.0, -5.0);
glPushMatrix();
glRotated((GLdouble) spin, 1.0, 1.0, 0.0);
glTranslated(0.0, 0.0, 1.5);
glDisable(GL_LIGHTING);
glColor3f(0.0, 1.0, 1.0);
glutWireCube(0.1);
glEnable(GL_LIGHTING);
glPopMatrix();
glutSolidTorus(0.275, 0.85, 8, 15);
glPopMatrix();
glFlush();
}
void reshape(int w, int h)
{
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
 gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

void display_mvwithviewport(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0);
    glutSolidTorus(0.275, 0.85, 8, 15);
    glPopMatrix();
glFlush();
}
void reshape_mvwithviewport(int w, int h)
{
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
 gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
GLfloat position[] = { 0.0, 0.0, 1.0, 1.0 };
// GLfloat position[] = { 1.0, 1.0, 1.0, 0.0 };
glLightfv(GL_LIGHT0, GL_POSITION, position);

}
void mouse(int button, int state, int x, int y)
{
switch (button) {
case GLUT_LEFT_BUTTON:
if (state == GLUT_DOWN) {
spin = (spin + 1) % 60;
glutPostRedisplay();
}
break;
default:
break;
}
}
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(500, 500);
glutInitWindowPosition(100, 100);
glutCreateWindow(argv[0]);
init();
// glutDisplayFunc(display);
// glutReshapeFunc(reshape);
glutDisplayFunc(display_mvwithviewport);
glutReshapeFunc(reshape_mvwithviewport);
 glutMouseFunc(mouse);
glutMainLoop();
return 0;
}
