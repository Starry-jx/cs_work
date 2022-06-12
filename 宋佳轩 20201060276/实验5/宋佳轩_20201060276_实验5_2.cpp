#include<stdlib.h>
#include<iostream>
#include<gl/glut.h>
#include<math.h>
using namespace std;
typedef float Color[3];
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 400, 0, 400);
}
void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void getPixel(GLint x, GLint y, Color c) {
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, c);

}
bool rgbColorEqual(Color c1, Color c2) {
	
	if ((fabs(c1[0] - c2[0]) > 0.001) || (fabs(c1[1] - c2[1]) > 0.001) || (fabs(c1[2] - c2[2]) > 0.001))
		return 0;
	else return 1;
}

void boundaryFill4(int x, int y, Color fillColor, Color  borderColor)
{
	Color interiorColor;
	/* Set current color to fillColor, then perform following oprations. */
	getPixel(x, y, interiorColor);
	glColor3f(fillColor[0], fillColor[1], fillColor[2]);
	if (rgbColorEqual(interiorColor, borderColor)) {
		setPixel(x, y);    // Set color of pixel to fillColor.  
		boundaryFill4(x + 1, y, fillColor, borderColor);
		boundaryFill4(x - 1, y, fillColor, borderColor);
		boundaryFill4(x, y + 1, fillColor, borderColor);
		boundaryFill4(x, y - 1, fillColor, borderColor);
	}
}
	void myDraw(void) {
		int x = 200, y = 150;
		Color fillColor, interiorColor;
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(100.0, 100.0);
		glVertex2f(100.0, 150.0);
		glVertex2f(250.0, 300.0);
		glVertex2f(300.0, 50.0);
		glEnd();
		fillColor[0] = 1.0;
		fillColor[1] = 0.0;
		fillColor[2] = 0.0;
		interiorColor[0] = 1;
		interiorColor[1] = 1;
		interiorColor[2] = 1;
		boundaryFill4(x, y, fillColor, interiorColor);
		glFlush();

	}
	void main(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
		glutInitWindowPosition(20, 100);
		glutInitWindowSize(400,400);
		glutCreateWindow("边界填充");
		init();
		glutDisplayFunc(myDraw);
		glutMainLoop();

	
	}