#include "myglwidget.h"
#include <GL/glu.h>

MyGLWidget::MyGLWidget(QWidget *parent) : QGLWidget(parent)
{

}

void MyGLWidget::initializeGL()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
   glClearDepth(1.0);
   glEnable(GL_DEPTH_TEST);
}

void MyGLWidget::resizeGL(int w, int h)
{
   glViewport(0, 0, (GLint)w, (GLint)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

//void MyGLWidget::paintGL()
//{
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   glLoadIdentity();
//   // 绘制三角形
//   glTranslatef(-2.0, 0.0, -6.0);
//   glBegin(GL_TRIANGLES);
//   glColor3f(1.0, 0.0, 0.0);
//   glVertex3f(0.0, 1.0, 0.0);
//   glColor3f(0.0, 1.0, 0.0);
//   glVertex3f(-1.0, -1.0, 0.0);
//   glColor3f(0.0, 0.0, 1.0);
//   glVertex3f(1.0, -1.0, 0.0);
//   glEnd();
//   // 绘制四边形
//   glTranslatef(4.0, 0.0, 0.0);
//   glBegin(GL_QUADS);
//   glColor3f(1.0, 1.0, 0.0);
//   glVertex3f(-1.0, 1.0, 0.0);
//   glVertex3f(1.0, 1.0, 0.0);
//   glVertex3f(1.0, -1.0, 0.0);
//   glVertex3f(-1.0, -1.0, 0.0);
//   glEnd();
//}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -6.0);
    glRotatef(45, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    // 上面
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    // 下面
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    // 前面
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glEnd();
}
