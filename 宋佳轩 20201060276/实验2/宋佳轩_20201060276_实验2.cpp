#include<stdlib.h>
#include<iostream>
#include<gl/glut.h>
#include<math.h>
using namespace std;
const int window_width = 600, window_height = 600;
class Point {
public:
	double x, y;
	Point() {

	}
};
//画点
void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void lineDDA(int x0, int y0, int xEnd, int yEnd) {
	int dx = xEnd - x0, dy = yEnd - y0, steps;//dx与dy即△x，△y 
	float xIncrement, yIncrement, x = x0, y = y0;
	steps=max(fabs(dx), fabs(dy));//steps=max(|△x|,|△y|)
	xIncrement = float(dx) / float(steps);
	yIncrement = float(dy) / float(steps);
	setPixel(round(x), round(y));
	for (int k = 0; k < steps; k++) {
		x += xIncrement;
		y += yIncrement;
		setPixel(round(x), round(y));
	}
}

void Display_DDA(void)
{
	Point a,b; //顶点a,b 
	cout << "输入a,b的坐标:\n";
	cin >> a.x >> a.y >> b.x >> b.y;
	lineDDA(a.x, a.y, b.x, b.y);//DDA算法生成直线段
	glFlush();
}
void init() {
	gluOrtho2D(0, window_width, 0, window_height);//确定窗口显示的坐标范围
	glColor3f(0.0, 0.4, 1.0);//确定点的颜色
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("DDA直线生成");
	init();
	glutDisplayFunc(Display_DDA);
	glutMainLoop();

	return 0;
}