#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<gl/glut.h>
#include<algorithm>
#include<vector>
float theta_ad = 0.0;
float theta_ws = 0.0;
double PI = 3.1415;
using namespace std;
double A[4][4] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
int oldx = 0;
int oldy = 0;
class Point3D {
public:
	float x, y, z;
	Point3D() {

	}
	Point3D(int i) {

		if (i == 1) {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}
		else if (i == 2) {
			this->x = 0;
			this->y = 0;
			this->z = 200;
		}
		else if (i == 3) {
			this->x = 200;
			this->y = 0;
			this->z = 200;
		}
		else if (i == 4) {
			this->x = 200;
			this->y = 0;
			this->z = 0;
		}
		else if (i == 5)
		{
			this->x = 50;
			this->z = 50;
			this->y = 200;
		}
		else if (i == 6)
		{
			this->x = 50;
			this->z = 150;
			this->y = 200;
		}
		else if (i == 7)
		{
			this->x = 150;
			this->z = 150;
			this->y = 200;
		}
		else if (i == 8)
		{
			this->x = 150;
			this->z = 50;
			this->y = 200;
		}
	}
};
vector<Point3D> vertice3D; //顶点
void initPixel() {
	Point3D p1(1), p2(2), p3(3), p4(4), p5(5), p6(6), p7(7), p8(8);
	vertice3D.push_back(p1);
	vertice3D.push_back(p2);
	vertice3D.push_back(p3);
	vertice3D.push_back(p4);
	vertice3D.push_back(p5);
	vertice3D.push_back(p6);
	vertice3D.push_back(p7);
	vertice3D.push_back(p8);
}
void setPixel(int p1, int p2, int p3, int p4) {
	glVertex3f(vertice3D[p1].x, vertice3D[p1].y, vertice3D[p1].z);
	glVertex3f(vertice3D[p2].x, vertice3D[p2].y, vertice3D[p2].z);
	glVertex3f(vertice3D[p3].x, vertice3D[p3].y, vertice3D[p3].z);
	glVertex3f(vertice3D[p4].x, vertice3D[p4].y, vertice3D[p4].z);
}
void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓存
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(theta_ad, 0.0f, 1.0f, 0.0f);
	glRotatef(theta_ws, 1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	setPixel(0, 1, 2, 3);
	glColor3f(0.0f, 1.0f, 0.0f);
	setPixel(4, 5, 6, 7);
	glColor3f(1.0f, 0.0f, 1.0f);
	setPixel(0, 4, 1, 5);
	glColor3f(.0f, 0.0f, 0.0f);
	setPixel(1, 5, 6, 2);
	glColor3f(1.0f, 0.5f, 0.5f);
	setPixel(6, 2, 3, 7);
	glColor3f(0.5f, 0.5f, 0.0f);
	setPixel(3, 7, 4, 0);
	glEnd();
	glutSwapBuffers();

}
void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 'a' || key == 'A')
		A[3][0] -= 5.0;
	if (key == 'd' || key == 'D')
		A[3][0] += 5.0;
	if (key == 'w' || key == 'W')
		A[3][1] += 5.0;
	if (key == 's' || key == 'S')
		A[3][1] -= 5.0;
	if (key == 'q' || key == 'Q')
		A[3][2] += 5.0;
	if (key == 'e' || key == 'E')
		A[3][2] -= 5.0;
	if (key == 'z' || key == 'Z')
		theta_ad += 5.0;
	if (key == 'x' || key == 'X')
		theta_ad -= 5.0;
	if (key == 'c' || key == 'C')
		theta_ws += 5.0;
	if (key == 'v' || key == 'V')
		theta_ws -= 5.0;
	if (theta_ad > 360) theta_ad -= 360;
	if (theta_ad < 0) theta_ad += 360;
	if (theta_ws > 360) theta_ws -= 360;
	if (theta_ws < 0) theta_ws += 360;
	if (key == 'b' || key == 'B')
		exit(0);


	for (int i = 0; i < vertice3D.size(); i++) {
		vertice3D[i].x = vertice3D[i].x * A[0][0] + vertice3D[i].y * A[1][0] + vertice3D[i].z * A[2][0] + A[3][0];
		vertice3D[i].y = vertice3D[i].x * A[0][1] + vertice3D[i].y * A[1][1] + vertice3D[i].z * A[2][1] + A[3][1];
		vertice3D[i].z = vertice3D[i].x * A[0][2] + vertice3D[i].y * A[1][2] + vertice3D[i].z * A[2][2] + A[3][2];
	}
	A[0][0] = A[1][1] = A[2][2] = 1;
	A[3][0] = A[3][1] = A[3][2] = A[1][2] = A[2][1] = A[0][2] = A[2][0] = 0;
	glutPostRedisplay(); //重新调用绘制函数
}


void reshape(int w, int h) //重绘回调函数，在窗口首次创建或用户改变窗口尺寸时被调用
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500.0, 500.0, -500.0, 500.0, 500.0, -500.0);
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);     //启动深度测试模式
}

void main(int argc, char** argv)
{
	cout << "WASDQE控制平移，zxcv控制旋转，b退出"<<endl;
	initPixel();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("3D widget");
	init();
	glutReshapeFunc(reshape); //指定重绘回调函数
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);   //指定键盘回调函数
	glutMainLoop();
}
