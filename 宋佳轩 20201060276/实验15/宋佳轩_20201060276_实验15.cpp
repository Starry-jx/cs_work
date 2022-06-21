#include <gl/glut.h>
float theta = 0.0, Xtheta = 0, Ytheta = 0, Ztheta = 0;//定义旋转角度、绕x轴旋转、绕y轴旋转
float oldx = 0, oldy = 0;//记录旧的点
float Rate = 1;//缩放比例
float XTran = 0, YTran = 0, ZTran = 0;//在x轴和y轴方向平移量
int winMax = 500, winMin = 500;//窗口大小
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕及深度缓存
	glLoadIdentity();							// 重置模型观察矩阵

	glTranslatef(0.0f, 0.0f, -6.0f);			// 移入屏幕 5 个单位
	glRotatef(Xtheta, 0.0f, 1.0f, 0.0f);			// 绕X轴旋转
	glRotatef(Ytheta, 1.0f, 0.0f, 0.0f);			// 绕Y轴旋转
	glRotatef(Ztheta, 0.0f, 0.0f, 1.0f);			// 绕Z轴旋转

	glDisable(GL_TEXTURE_2D);

	glColorMask(0, 0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPolygonOffset(1.1f, 4.0f);
	glEnable(GL_POLYGON_OFFSET_FILL);  //启用多边形偏移
	glutSolidTeapot(1.0f);

	glDisable(GL_POLYGON_OFFSET_FILL);
	glColorMask(1, 1, 1, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glutSolidTeapot(1.0f);

	glutSwapBuffers();
	glutPostRedisplay();
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
	render();
}

void mouseMove(int button, int state, int x, int y)//实现摁住鼠标移动观察茶壶
{
	oldx = x;//当左键按下时记录鼠标坐标
	oldy = y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glutMotionFunc(motionROt);
	}

}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.f, (GLfloat)w / h, 0.1f, 100.f);

	glMatrixMode(GL_MODELVIEW);
}
void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	 glutCreateWindow("消隐算法");
	init();
	glutReshapeFunc(resize);
	glutDisplayFunc(render);
	 	glutIdleFunc(render);
		glutMouseFunc(mouseMove);
	glutMainLoop();

	return 0;
}