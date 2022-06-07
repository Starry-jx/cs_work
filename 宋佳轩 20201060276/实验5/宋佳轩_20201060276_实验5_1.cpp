#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<gl/glut.h>
#include<algorithm>
#include<vector>
using namespace std;
const int window_width = 600, window_height = 600;
void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void init() {
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-300, 300, -300, 300);
	glClearColor(1, 1, 1, 1);
}
void circleBresenham() {
	int x, y, R, d;
	cout << "请输入半径：";
	cin >> R;
	d = 1.25 - R;
	x = 0;
	y = R;
	while (x < y) {
		setPixel(x, y);
		setPixel(y, x);
		setPixel(y, -x);
		setPixel(-x, y);
		setPixel(-x, -y);
		setPixel(-y, -x);
		setPixel(-y, x);
		setPixel(x, -y);
		if (d <= 0) {
			d = d + 2 * x + 3;
			x = x + 1;

		}
		else {
			d = d + 2 * (x - y) + 5;
			x = x + 1;
			y = y - 1;

		}
	}
}
void Display_circleBre() {
	glColor3f(0.0, 0.4, 0.2);
	glPointSize(1);
	circleBresenham();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(window_width, window_height);
			glutCreateWindow("中点Bresenham画圆");
			init();
			glutDisplayFunc(&Display_circleBre);
			glutMainLoop();

	return 0;
}
