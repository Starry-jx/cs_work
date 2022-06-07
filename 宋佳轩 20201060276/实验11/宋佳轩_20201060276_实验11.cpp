#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<gl/glut.h>
#include<algorithm>
#include<vector>
float x = 100.0, y = 100.0; //直线的第一个端点
float w = 0, l = 0;
using namespace std;
struct point
{
    float x, y;
    point(int xx, int yy) :
        x(xx), y(yy) {}
};
vector<point> vertice; //顶点
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}
//画线
void setLine(point p1, point p2) {
    glBegin(GL_LINES);
    glVertex2i(p1.x, p1.y);
    glVertex2i(p2.x, p2.y);
    glEnd();
    glFlush();
}
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 600.0, 0.0, 600.0);
}

void display_1(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x + l, y + w);
    glVertex2f(x + l, y + w + 200);
    glVertex2f(x + l + 300, y + w + 200);
    glVertex2f(x + l + 300, y + w);
    glEnd();
    glutSwapBuffers();     //交换前后台缓存
}

void myKeyboard(unsigned char key, int x, int y)
{
    if (key == 'w' || key == 'W')
        w += 5.0;
    if (key == 's' || key == 'S')
        w -= 5.0;
    if (key == 'a' || key == 'A')
        l -= 5.0;
    if (key == 'd' || key == 'D')
        l += 5.0;
    if (key == 'c' || key == 'C')
        exit(0);
    glutPostRedisplay(); //重新调用绘制函数
}
void display_2(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 1.0);

}
void myMouse(int button, int state, int x, int y)
{
    //按下鼠标左键
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        point p(x, 600 - y);
        if (vertice.size() == 1) {
            setLine(vertice[0], p);
            vertice.clear();
        }
        else {
            vertice.push_back(p);
            setPixel(p.x, p.y);
        }
    }
    //按下鼠标右键
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        glClear(GL_COLOR_BUFFER_BIT);
        setPixel(0, 0);
    }
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        exit(0);
    }


}
void main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Draw Triangle with Double Buffer");
    init();
    glutDisplayFunc(display_1);
    glutKeyboardFunc(myKeyboard);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Draw Triangle with Double Buffer");
    init();
    glutDisplayFunc(display_2);
    glutMouseFunc(myMouse);
    glutMainLoop();

}