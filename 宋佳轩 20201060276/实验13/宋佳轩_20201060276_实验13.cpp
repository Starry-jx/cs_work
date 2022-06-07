#include <gl/glut.h>
#include<iostream>
GLsizei winWidth = 500, winHeight = 500;
using namespace std;
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
void displayWirePolyhedra(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glScalef(1.5, 2.0, 1.0);
	glutWireCube(1.0);

	glScalef(0.8, 0.5, 0.8);
	glTranslatef(-6.0, -5.0, 0.0);
	glutWireDodecahedron();

	glTranslatef(8.6, 8.6, 2.0);
	glutWireTetrahedron();

	glTranslatef(-3.0, -1.0, 0.0);
	glutWireOctahedron();

	glScalef(0.8, 0.8, 1.0);
	glTranslatef(4.3, -2.0, 0.5);
	glutWireIcosahedron();

	glFlush();
}
void wireQuqdSurfs(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	glPushMatrix();
	glTranslatef(1.0, 1.0, 0.0);
	glutWireSphere(0.75, 8, 6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, -0.5, -0.5);
	glutWireCone(0.7, 2.0, 7, 6);
	glPopMatrix();

	GLUquadricObj* cylinder;
	glPushMatrix();
	glTranslatef(0.0, 1.2, 0.8);
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.6, 0.6, 1.5, 6, 4);
	glPopMatrix();
	glFlush();
}
void winReshapeFcn_1(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
}
void winReshapeFcn_2(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
}
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Wire-Frame Polyhedra");
	init();
	glutDisplayFunc(displayWirePolyhedra);
	glutReshapeFunc(winReshapeFcn_1);

	glutCreateWindow("Wire-Frame Quardric SurFaces");
	init();
	glutDisplayFunc(wireQuqdSurfs);
	glutReshapeFunc(winReshapeFcn_2);

	glutMainLoop();
}

