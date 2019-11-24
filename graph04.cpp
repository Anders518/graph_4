#include<windows.h>
//#include"stdafx.h"
#include<GL/glut.h>
#include<math.h>

#define N 1000 //线段最大条数
#define Pi 3.1415926
int ww, hh; //显示窗口宽和高
int n = 100;
float R;
float M;
int line[N][4], k = 0; //线段坐标储存数组，线段计数

void Myinit(void);
void Reshape(int w, int h);
void Display(void);
void myMouse(int button, int state, int x, int y);
void myMotion(int x, int y);
void drawLines();
void drawRect();
void drawCircular();

int main(int argc, char** argv)
{


    glutInit(&argc, argv);    //初始化GLUT库；
    glutInitWindowSize(800, 600);//绘制窗口大小
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //设置显示模式；（缓冲，颜色类型）双缓存
    glutCreateWindow("hello");  //创建窗口
    Myinit();

    glutDisplayFunc(Display);  //注册显示回调函数用于绘制当前窗口
    glutMouseFunc(myMouse);    //注册鼠标按钮回调函数
    glutMotionFunc(myMotion);  //注册鼠标移动回调函数
    glutReshapeFunc(Reshape);  //注册窗口改变回调函数

    glutMainLoop();   //表示开始运行程序，用于程序的结尾；
    return 0;

}


void Myinit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glLineWidth(3.0);
}
//渲染绘制子程序
//---------------------------------------------------------------
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //刷新颜色缓存区
    drawRect();     //画线子程序
    glutSwapBuffers();    //双缓存的刷新模式
}
//---------------------------------------------------------------
void Reshape(int w, int h)  //窗口改变时自动获取显示窗口的宽w和高h
{
    glMatrixMode(GL_PROJECTION); //投影矩阵模式
    glLoadIdentity();    //矩阵堆栈清空
    glViewport(0, 0, w, h);   //设置视区大小
    gluOrtho2D(0, w, 0, h);   //设置裁剪视区大小
    ww = w;
    hh = h;
}


//鼠标按钮响应事件
void myMouse(int button, int state, int x, int y)
{
    //鼠标左键按下——确定起始点
    //鼠标左键松开——画最后一个顶点，画线结束
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        line[k][0] = x;   //线段起点x坐标
        line[k][1] = hh - y;  //线段终点y坐标
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        line[k][2] = x;   //线段起点坐标
        line[k][3] = hh - y;  //线段终点坐标
        k++;
        glutPostRedisplay();
    }
}


//鼠标移动时获得鼠标移动中的坐标
void myMotion(int x, int y)
{
    //鼠标移动——线画到哪
    line[k][2] = x;   //动态终点的x坐标
    line[k][3] = hh - y;  //动态终点的y坐标
    glutPostRedisplay();
}

//画线子程序


void drawLines()
{
    for (int i = 0; i <= k; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(line[i][0], line[i][1]);
        glVertex2f(line[i][2], line[i][3]);
        glEnd();
    }
}



void drawRect()
{
    for (int i = 0; i <= k; i++)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//这个语句的作用告诉opengl只画出边框，但不填充内部。运行效果如下:
        glRectf(line[i][0], line[i][1], line[i][2], line[i][3]); //绘制矩形
    }
}



void drawCircular()
{

    for (int i = 0; i <= k; i++)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        M = (line[i][0] - line[i][2]) * (line[i][0] - line[i][2]) + (line[i][1] - line[i][3]) * (line[i][1] - line[i][3]);
        R = sqrt(M);
        for (int j = 0; j < n; j++)
        {
            glVertex2f(line[i][0] + R * cos(2 * Pi / n * j), line[i][1] + R * sin(2 * Pi / n * j));
        }
        glEnd();
    }
}