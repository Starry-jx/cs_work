#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<gl/glut.h>
#include<algorithm>
using namespace std;
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
	float k = fabs((float)(yEnd - y0) / (xEnd - x0));//判断斜率与1的关系
	if (k > 1) {//画斜率大于1和小于-1的直线
		int c = 1;//通过c的1和-1的不同实现正负斜率的直线的绘制
		if (y0 > yEnd) {//确保起始点的y值小于结束点的
			swap(x0, xEnd);
			swap(y0, yEnd);
		}
		k = (float)(xEnd - x0) / (yEnd - y0);
		if (k < 0) {  //判断斜率的正负，c=1为正斜率，c=-1为负斜率
			c = -1;
		}
		k = fabs(k);
		float d = 0;
		int x = x0, y = y0;
		setPixel(round(x), round(y));
		while (y < yEnd) {
			d = d + k;
			if (d > 0.5) {
				x=c+x;
				d--;
			}
			setPixel(round(x), round(++y));
		}
	}
	else {//画斜率小于1并大于-1的直线
		int c = 1;//通过c的1和-1的不同实现正负斜率的直线的绘制
		if (x0 > xEnd) {   //确保起始点的x值小于结束点的
			swap(x0, xEnd);
			swap(y0, yEnd);
		}
		k = (float)(yEnd - y0) / (xEnd - x0);
		if (k < 0) {//判断斜率的正负
			c = -1; //判断斜率的正负，c=1为正斜率，c=-1为负斜率
		}
		k = fabs(k);
		float d = 0;
		int x = x0, y = y0;
		setPixel(round(x), round(y));
	while (x < xEnd) {
		d = d + k;
		if (d > 0.5){
		y=y+c;
		d--; 
		}
	setPixel(round(++x), round(y));
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
	glColor3f(0.0, 1.0, 0.0);
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