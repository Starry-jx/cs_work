#include <gl/glut.h>
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  // 指定清空颜色（背景色）为黑色
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);   //指定二维坐标系中被显示的区域
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  // 清空显示窗口
    glColor3f(1.0, 1.0, 1.0);      // 指定前景色（当前绘制颜色）为白色
    glBegin(GL_POINTS);            //单个点
    glVertex2i(100,200);       
    glEnd();
    glBegin(GL_LINES);      //线段
    glVertex2i(0, 0);       
    glVertex2i(300, 100);
    glEnd();
    glBegin(GL_LINE_LOOP);//三角形
    glVertex2i(400, 300);   
    glVertex2i(600, 300);
    glVertex2i(500, 500);
    glEnd();
    glBegin(GL_POLYGON);//填充三角形
    glVertex2i(400, 50);       
    glVertex2i(600, 50);
    glVertex2i(500, 250);
    glEnd();
    glFlush();     // 使绘制立即反映到屏幕上
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);                         // 初始 GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //设定显示模式
    glutInitWindowPosition(0, 0);   // 设定窗口位置
    glutInitWindowSize(800, 600);      // 设定窗口大小
    glutCreateWindow("OpenGL基本图元绘制"); // 用前面指定参数创建窗口，并定义窗口名称
    init();                            // 进行一些初始化工作
    glutDisplayFunc(display);       // 指定绘制的回调函数
    glutMainLoop();          // 进入无穷循环，等待事件处理
}