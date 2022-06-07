#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<gl/glut.h>
#include<algorithm>
#include<vector>
using namespace std;
const double PI = 3.14159;
const int window_width = 600, window_height = 600;
class Point {
public:
	double x, y;
	Point() {

	}
};
void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void lineBresenham(int x0, int y0, int xEnd, int yEnd) {
	int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
	int x, y;
	if (dx > dy) {
		int p = 2 * dy - dx;
		int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
		if (x0 > xEnd) {
			x = xEnd;
			y = yEnd;
			xEnd = x0;
		}
		else {
			x = x0;
			y = y0;
		}

		setPixel(round(x), round(y));
		while (x < xEnd) {
			x++;
			if (p < 0)
				p += twoDy;
			else {
				y++;
				p += twoDyMinusDx;
			}
			setPixel(round(x), round(y));
		}
	}
	else {
		int p = 2 * dx - dy;
		int twoDy = 2 * dx, twoDyMinusDx = 2 * (dx - dy);
		if (y0 > yEnd) {

			x = xEnd;
			y = yEnd;
			yEnd = y0;
		}
		else {
			x = x0;
			y = y0;
		}
		setPixel(round(x), round(y));
		while (y < yEnd) {
			y++;
			if (p < 0)
				p += twoDy;
			else {
				x++;
				p += twoDyMinusDx;
			}
			setPixel(round(x), round(y));
		}
	}


}
void Display_lineBre(void)
{
	Point a, b; //顶点a,b 
	cout << "输入a,b的坐标:\n";
	cin >> a.x >> a.y >> b.x >> b.y;
	lineBresenham(a.x, a.y, b.x, b.y);
	glFlush();
}
void init() {
	gluOrtho2D(0, window_width, 0, window_height);
	glColor3f(0.0, 0.0, 1.0);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Bresenham直线生成");
	init();
	glutDisplayFunc(Display_lineBre);
	glutMainLoop();
	return 0;
}