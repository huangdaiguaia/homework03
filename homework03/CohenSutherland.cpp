#include "stdlib.h"
#include "GL/glut.h"
#define  LEFT      1     // 0001，左
#define  RIGHT     2     // 0010，右
#define  BOTTOM    4     // 0100，下
#define  TOP       8     // 1000，上
//#define  XL       -250
//#define  XR       250
//#define  YT       250
//#define  YB       -250
int XL = -250, XR = 250, YT = 250, YB = -250;

void DisplayLine(int x1, int y1, int x2, int y2) {
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

// 已知端点坐标(x,y)，求其所在区的编码code。
void encode(int x, int y, int *code)
{
	int c = 0;
	if (x<XL)  c = c | LEFT;
	else  if (x>XR) c = c | RIGHT;
	if (y<YB)  c = c | BOTTOM;
	else  if (y>YT)   c = c | TOP;
	*code = c;
	return;
}
//画出剪切线
void C_S_Line(int x1, int  y1, int  x2, int y2)
{
	int code1, code2, code, x, y;
	encode(x1, y1, &code1);
	encode(x2, y2, &code2);                                // 求出两个端点处的编码
	while (code1 != 0 || code2 != 0)                         // “||”或者运算
	{
		if ((code1&code2) != 0)
			return;
		code = code1;
		if (code1 == 0)  code = code2;
		if ((LEFT&code) != 0)                              //线段与左边界的交点
		{
			x = XL;
			y = y1 + (y2 - y1)*(XL - x1) / (x2 - x1);
		}
		else if ((RIGHT&code) != 0)                        //线段与右边界的交点
		{
			x = XR;
			y = y1 + (y2 - y1)*(XR - x1) / (x2 - x1);
		}
		else  if ((BOTTOM&code) != 0)                       //线段与下边界的交点
		{
			y = YB;
			x = x1 + (x2 - x1)*(YB - y1) / (y2 - y1);
		}
		else if ((TOP&code) != 0)                            //线段与上边界的交点
		{
			y = YT;
			x = x1 + (x2 - x1)*(YT - y1) / (y2 - y1);
		}
		if (code == code1)
		{
			x1 = x;
			y1 = y; encode(x, y, &code1);
		}
		else
		{
			x2 = x;
			y2 = y; encode(x, y, &code2);
		}
	} //end-while
	DisplayLine(x1, y1, x2, y2);
}  //End C_S_Clip() 



void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINE_LOOP);
	glVertex2d(-250, -250);
	glVertex2d(-250, 250);
	glVertex2d(250, 250);
	glVertex2d(250, -250);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	DisplayLine(-100, 100, 200, 200);
	DisplayLine(-300, 50, 100, -300);
	DisplayLine(100, -400, 400, -300);
	DisplayLine(-100, -100, 450, 100);


	glColor3f(0.0, 1.0, 0.0);
	C_S_Line(-100, 100, 200, 200);
	C_S_Line(-300, 50, 100, -300);
	C_S_Line(100, -400, 400, -300);
	C_S_Line(-100, -100, 450, 100);

	glFlush(); 
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glColor3f(0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500, 500.0, -500, 500.0, 0.0, 1.0);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);                         
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowSize(500, 500);             
	glutInitWindowPosition(0, 0);            
	glutCreateWindow("简单示例");            
	glutDisplayFunc(mydisplay);                 
	init();                                      
	glutMainLoop();                               
}
