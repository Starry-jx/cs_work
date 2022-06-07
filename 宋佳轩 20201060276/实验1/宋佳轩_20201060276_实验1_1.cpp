#include<gl/glut.h>
#include<stdlib.h>
const int window_width = 600, window_height = 600;
void Display_example()
{
	glBegin(GL_LINES);
	glVertex2i(450, 600);       // 指定顶点
	glVertex2i(100, 145);
	glEnd();
	glFlush();     // 使绘制立即反映到屏幕上
}
void init() {
	gluOrtho2D(0, window_width, 0, window_height);//指定屏幕区域对应的模型坐标范围
	glColor3f(0.0, 0.0, 1.0);      // 指定绘制颜色为蓝色
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);//确定窗口位置
	glutInitWindowSize(window_width, window_height);//确定窗口大小
	glutCreateWindow("An Example OpenGL Program");//图像名称
	init();
	glutDisplayFunc(Display_example);
	glutMainLoop();
	return 0;
}
