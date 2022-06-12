#include <gl/glut.h>

GLuint lineList; //指定显示列表ID
void Initial()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glLineWidth(12.0f);                 
	glColor4f(0.0, 0.6, 1.0, 1.0);     
	lineList = glGenLists(1);          
	glNewList(lineList, GL_COMPILE);  
	glBegin(GL_LINE_LOOP);       
	glVertex2f(1.0f, 1.0f);    
	glVertex2f(4.0f, 2.0f);    
	glVertex2f(2.0f, 5.0f);     
	glEnd();                      
	glEndList();                    
}

void ChangeSize(GLsizei w, GLsizei h) 
{
	if (h == 0)		h = 1;
	glViewport(0, 0, w, h);         
	glMatrixMode(GL_PROJECTION);     
	glLoadIdentity();                
	if (w <= h)
		gluOrtho2D(0.0, 5.0, 0.0, 6.0 * (GLfloat)h / (GLfloat)w);//更改模型坐标范围
	else
		gluOrtho2D(0.0, 5.0 * (GLfloat)w / (GLfloat)h, 0.0, 6.0);//更改模型坐标范围
	glMatrixMode(GL_MODELVIEW);      //模型视景的操作 
	glLoadIdentity();              //重置当前指定的矩阵为单位矩阵
}

void Displayt(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//用当前背景色填充窗口
	glCallList(lineList);        //函数执行显示列表
	glFlush();                  //强制刷新缓冲，保证绘图命令将被执行 
}

void Displayw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);  
	glEnable(GL_LINE_SMOOTH);      //使用反走样
	glEnable(GL_BLEND);             //启用混合函数
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //指定混合函数
	glCallList(lineList); //函数执行显示列表
	glFlush();            

}

void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(300, 300);                
	glutCreateWindow("原始图形");                 
	glutDisplayFunc(Displayt);                   
	glutReshapeFunc(ChangeSize);
	Initial();

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(300, 300);
	glutCreateWindow("反走样图形");
	glutDisplayFunc(Displayw);
	glutReshapeFunc(ChangeSize);
	Initial();
	glutMainLoop();
}
