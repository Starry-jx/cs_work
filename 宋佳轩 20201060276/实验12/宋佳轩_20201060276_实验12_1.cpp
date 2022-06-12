#include <stdlib.h>
#include <GL/glut.h>  
float theta_ad = 0.0;
float theta_ws = 0.0;
void drawPyramid()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireTeapot(0.8);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓存
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(theta_ad, 0.0f, 1.0f, 0.0f);
	glRotatef(theta_ws, 1.0f, 0.0f, 0.0f);
	drawPyramid();
	glutSwapBuffers();

}

void reshape(int w, int h) //重绘回调函数，在窗口首次创建或用户改变窗口尺寸时被调用
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, 10.0);
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);     //启动深度测试模式
}

void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 'a' || key == 'A')
		theta_ad += 5.0;
	if (key == 'd' || key == 'D')
		theta_ad -= 5.0;
	if (key == 'w' || key == 'W')
		theta_ws += 5.0;
	if (key == 's' || key == 'S')
		theta_ws -= 5.0;
	if (key == 'c' || key == 'C')
		exit(0);
	if (theta_ad > 360) theta_ad -= 360;
	if (theta_ad < 0) theta_ad += 360;
	if (theta_ws > 360) theta_ws -= 360;
	if (theta_ws < 0) theta_ws += 360;
	glutPostRedisplay(); //重新调用绘制函数
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("茶壶---WASD控制旋转方向,C键:退出");
	init();
	glutReshapeFunc(reshape); //指定重绘回调函数
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);   //指定键盘回调函数
	glutMainLoop();
}
