#include<gl/glut.h>
#include<math.h>
using namespace std;
const int window_width = 600, window_height = 600;
const double TWO_PI = 6.283153;
GLuint regHex;
class screenPt {
private:
	GLint x, y;
public:
	screenPt() {
		x = y = 0;
	}
	void setCoords(GLint xCoord, GLint yCoord) {
		x = xCoord;
		y = yCoord;
	}
	GLint getx() const { return x; }
	GLint gety() const { return y; }
};
static void init_scan(void) {
	screenPt hexVertex, circCtr;
	GLdouble theta;
	GLint k;
	circCtr.setCoords(window_width / 2, window_height / 2);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	regHex = glGenLists(1);//构造多边形
	glNewList(regHex, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 6; k++) {
		theta = TWO_PI * k / 6.0;
		hexVertex.setCoords(circCtr.getx() + 150 * cos(theta), circCtr.gety() + 150 * sin(theta));
		glVertex2i(hexVertex.getx(), hexVertex.gety());
	}
	glEnd();
	glEndList();
}
void regHexagon(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glCallList(regHex);
	glFlush();
}
void winReshapeFcn(int newWidth, int newHeight) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Reshape-Function & Display - List Example");
	init_scan();
	glutDisplayFunc(regHexagon);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}
