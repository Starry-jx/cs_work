#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <gl/glut.h>
#include <math.h>
#include<iostream>
using namespace std;
#define BITMAP_ID 0x4D42
#define Height 16
#define Width 16
float theta = 0.0, Xtheta = 0, Ytheta = 0, Ztheta = 0;//定义旋转角度、绕x轴旋转、绕y轴旋转
float oldx = 0, oldy = 0;//记录旧的点
float Rate = 1;//缩放比例
float XTran = 0, YTran = 0, ZTran = 0;//在x轴和y轴方向平移量
int winMax = 500, winMin = 500;//窗口大小


GLint light_ch = 0;//光照开关

//初始化光源性质
void init()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat white_light[] = { 0.0, 1.0, 1.0, 1.0 };
	GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 }; //
	GLfloat light_position1[] = { 0.0, -3.0, 0.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//材质属性中的镜面反射光
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//材质属性的镜面反射指数
	/*glLightfv（光源编号，光源特性，参数数据）
	GL_AMBIENT（设置光源的环境光属性，默认值(0,0,0,1)）、GL_DIFFUSE（设置光源的散射光属性，默认值(1,1,1,1)）
	GL_SPECULAR（设置光源的镜面反射光属性，默认值(1,1,1,1)）、GL_POSITION（设置光源的位置，默认值(0,0,1,0)）*/
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//设置0号光源位置
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);//设置0号光源散射光属性
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);//设置0号镜面反射光属性
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);
	glEnable(GL_LIGHTING);//开启0号光源
	glEnable(GL_DEPTH_TEST);

}
//绘制茶壶
void drawTeapot()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glutSolidTeapot(1);
		glPopMatrix();
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓存
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -4.0f);//平移三维裁剪窗口，让窗口能完全包含住物体
	glRotatef(Xtheta, 0.0f, 1.0f, 0.0f);//根据鼠标移动距离旋转物体
	glRotatef(Ytheta, 1.0f, 0.0f, 0.0f);
	glRotatef(Ztheta, 0.0f, 0.0f, 1.0f);
	drawTeapot();
	glutSwapBuffers();
}

void reshape(int w, int h) //重绘回调函数，在窗口首次创建或用户改变窗口尺寸时被调用
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	if (w <= h)

		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,

			1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);

	else

		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h,

			1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 10.0);
}

void motionROt(int x, int y)//实现摁住时，计算旋转量，实现旋转
{
	GLint deltax = x - oldx;
	GLint deltay = y - oldy;
	Xtheta += 360 * (GLfloat)deltax / (GLfloat)winMax / 5;//根据屏幕上鼠标滑动的距离来设置旋转的角度
	Ytheta += 360 * (GLfloat)deltay / (GLfloat)winMin / 5;
	Ztheta += 360 * (GLfloat)deltay / (GLfloat)winMin / 5;
	oldx = x;//记录此时的鼠标坐标，更新鼠标坐标
	oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控
			glEnable(GL_LIGHTING);//开启0号光源
	display();
}

void mouseMove(int button, int state, int x, int y)//实现摁住鼠标移动观察茶壶
{
	oldx = x;//当左键按下时记录鼠标坐标
	oldy = y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glutMotionFunc(motionROt);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (light_ch == 1) {
			glDisable(GL_LIGHT0);
			cout << "关闭光照" << endl;
			light_ch = 0;
		}
		else {
			glEnable(GL_LIGHT0);//开启光照效果
			cout << "开启光照" << endl;
			light_ch = 1;
		}


		display();
	}
}

int main(int argc, char** argv)
{
	cout << "鼠标左键实现茶壶的旋转" << endl;
	cout << "鼠标右键实现灯光的开关" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winMax, winMin);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("光照");
	glutReshapeFunc(reshape); //指定重绘回调函数
	glutDisplayFunc(display);
	glutMouseFunc(mouseMove);
	init();
	glutMainLoop();
}