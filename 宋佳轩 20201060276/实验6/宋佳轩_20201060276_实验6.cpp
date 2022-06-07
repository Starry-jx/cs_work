#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<gl/glut.h>
#include<algorithm>
#include<vector>
using namespace std;
const double PI = 3.14159;
const int window_width = 600, window_height = 600;

struct point
{
	float x, y;
	point(int xx, int yy) :
		x(xx), y(yy) {}
};
vector<point> vertice; //顶点
void setPixel(point p) {
	glBegin(GL_POINTS);
	glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
}
void setGraph(vector<point> v) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < v.size(); i++)
		glVertex2f(v[i].x,v[i]. y);
	glEnd();
	glFlush();

}
void Two_geometric() {
	vector<point> vertice_;
	double angle;//旋转角度
	int select, end = 1;
	do {
		double A[3][3] = { 1,0,0, 0,1,0, 0,0,1 };
		cout << "1__平移 2__旋转" << "3__比例 4__对称" << "5__退出" << endl << "选择：";
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "x,y平移量:";
			cin >> A[2][0] >> A[2][1];
			glColor3f(1, 1, 1);
			break;
		case 2:
			cout << "旋转度数：";
			cin >> angle;
			angle = angle * PI / 180;
			A[0][0] = A[1][1] = cos(angle);
			A[0][1] = sin(angle);
			A[1][0] = -sin(angle);
			glColor3f(1, 1, 0.5);
			break;
		case 3:
			cout << "缩放比例：";
			cin >> A[0][0];
			A[1][1] = A[0][0];
			glColor3f(1, 0.5, 1);
			break;
		case 4:
			A[0][0] = 0;
			A[1][0] = 1;
			A[0][1] = 1;
			A[1][1] = 0;
			glColor3f(0.5, 1, 1);
			break;
		default:
			end = 0;
			break;
		}
		for (int i = 0; i < vertice.size(); i++) {
			point p(vertice[i].x * A[0][0] + vertice[i].y * A[1][0] + A[2][0], vertice[i].x * A[0][1] + vertice[i].y * A[1][1] + A[2][1]);
			vertice_.push_back(p);
		}
		setGraph(vertice_);
		vertice_.clear();
	} while (end == 1);


}
void wcPtD_mouse(int button, int state, int x, int y)
{

	//左键按下
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		point p(x, window_height - y);
		setPixel(p);
		vertice.push_back(p);
	}
	//左键松开
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		glColor3f(0, 1, 1);
		setGraph(vertice);
	}
	//右键
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		Two_geometric();
	}
}
void Display_wcPtD() {
	cout << "鼠标左键确定一个点，鼠标右键进入变换菜单" << endl;
}
void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, window_width, 0, window_height);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("二维矩阵变换");
	init();
	glutDisplayFunc(Display_wcPtD);
	glutMouseFunc(wcPtD_mouse);
	glutMainLoop();
	return 0;
}