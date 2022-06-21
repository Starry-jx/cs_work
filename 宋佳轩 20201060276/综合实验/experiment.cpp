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

GLuint texture[4];// 纹理标示符数组，保存两个纹理的标示符
GLint ch = 0;//纹理选择
GLint light_ch = 0;//光照开关
//读纹理图片
unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader)
{
	FILE* filePtr;    // 文件指针
	BITMAPFILEHEADER bitmapFileHeader;    // bitmap文件头
	unsigned char* bitmapImage;        // bitmap图像数据
	int    imageIdx = 0;        // 图像位置索引
	unsigned char    tempRGB;    // 交换变量

								// 以“二进制+读”模式打开文件filename 
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL) {
		printf("file not open\n");
		return NULL;
	}
	// 读入bitmap文件图
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	// 读入bitmap信息头
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// 验证内存是否创建成功
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 关闭bitmap图像文件
	fclose(filePtr);
	return bitmapImage;
}
//加载纹理的函数
void texload(int i, char* filename)
{
	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头
	unsigned char* bitmapData;                                       // 纹理数据

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,
		0,         //mipmap层次(通常为，表示最上层) 
		GL_RGB,    //我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2 
		bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2 
		0, //边框(0=无边框, 1=有边框) 
		GL_RGB,    //bitmap数据的格式
		GL_UNSIGNED_BYTE, //每个颜色数据的类型
		bitmapData);    //bitmap数据指针  

}

//初始化光源性质，初始化贴图
void init()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
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
	glEnable(GL_DEPTH_TEST);
	
	glGenTextures(4, texture); // 第一参数是需要生成标示符的个数, 第二参数是返回标示符的数组
	texload(3, "4.bmp");
	texload(1, "2.bmp");
	texload(2, "3.bmp");
}
//绘制茶壶
void drawTeapot() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	if(ch!=0){
	glBindTexture(GL_TEXTURE_2D, texture[ch]);  //选择纹理texture[status]
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//设置纹理受光照影响
	glutSolidTeapot(1);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);    //关闭纹理texture[status]
	}
	else
		glutSolidTeapot(1);
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
	Xtheta += 360 * (GLfloat)deltax / (GLfloat)winMax/5;//根据屏幕上鼠标滑动的距离来设置旋转的角度
	Ytheta += 360 * (GLfloat)deltay / (GLfloat)winMin / 5;
	Ztheta += 360 * (GLfloat)deltay / (GLfloat)winMin / 5;
	oldx = x;//记录此时的鼠标坐标，更新鼠标坐标
	oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控
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
			glDisable(GL_LIGHTING);
			cout << "关闭光照" << endl;
				light_ch = 0;
		}
		else {
			glEnable(GL_LIGHTING);//开启光照效果
			cout << "开启光照" << endl;
			light_ch = 1;
		}
		
		glEnable(GL_LIGHT0);//开启0号光源
		display();
	}
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		if (ch == 3)
			ch = 0;
		else
		   ch++;
		display();
	}
}

int main(int argc, char** argv)
{
	cout << "鼠标左键实现茶壶的旋转" << endl;
	cout << "鼠标右键实现灯光的开关" << endl;
	cout << "鼠标中键实现贴图的转换" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winMax, winMin);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("三维图形渲染");
	glutReshapeFunc(reshape); //指定重绘回调函数
	glutDisplayFunc(display);
	glutMouseFunc(mouseMove);
	init();
	glutMainLoop();
} 