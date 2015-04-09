#include<GL/freeglut.h>
/* Here is where the light position is reset after the modeling
* transformation (glRotated) is called. This places the
* light at a new position in world coordinates. The cube
* represents the position of the light.
*/

void init(void)
{
glClearColor(1.0, 1.0, 0.0, 0.0);
glBlendFunc(GL_ONE, GL_ONE);
glEnable(GL_BLEND);
}

void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0, 0.0, 1.0);
 glRectf(-0.5, -0.5, 0.5, 0.5);
glFlush();
}
void keyboard(unsigned char key, int x, int y)
{
switch (key) {
case 'a': case 'A':
/* Colors are added as: (1,1,0) + (0,0,1) = (1,1,1) which
* will produce a white square on a yellow background. */
glBlendEquation(GL_FUNC_ADD);
break;
case 's': case 'S':
/* Colors are subtracted as: (0,0,1) - (1,1,0) = (-1,-1,1)
* which is clamped to (0, 0, 1), producing a blue square
* on a yellow background. */
glBlendEquation(GL_FUNC_SUBTRACT);
break;
case 'r': case 'R':
/* Colors are subtracted as: (1,1,0) - (0,0,1) = (1,1,-1)
* which is clamped to (1, 1, 0). This produces yellow for
* both the square and the background. */
glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
break;
case 'm': case 'M':
/* The minimum of each component is computed, as
* [min(1,0),min(1,0),min(0,1)] which equates to (0,0,0).
* This will produce a black square on the yellow
* background. */
glBlendEquation(GL_MIN);
break;
case 'x': case 'X':
/* The minimum of each component is computed, as
* [max(1, 0), max(1, 0), max(0, 1)] which equates to
* (1, 1, 1). This will produce a white square on the
* yellow background. */
glBlendEquation(GL_MAX);
break;
default:
exit(0);
break;
}
glutPostRedisplay();
}
void reshape(int w, int h)
{
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
 glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
 // gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(500, 500);
glutInitWindowPosition(100, 100);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(display);
 glutKeyboardFunc(keyboard);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}
