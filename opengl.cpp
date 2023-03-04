#include <opengl.h>
#include<QDebug>
#include<iostream>
#include<QTime>
#include<GL/glut.h>
#include<point.h>
#include<nbodycalculate.h>


opengl::opengl(QWidget *parent)
    : QOpenGLWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus);
//    setMouseTracking(true);//感觉不需要这个 因为更喜欢按下鼠标并拖动来移动视角

    connect(timer, &QTimer::timeout, this, [=](){
        timeout();
    });
    timer->setInterval(1);


    camera.Position = QVector3D(0,-3500,2500);      //相机的初始位置
    camera.Yaw = -90.0f;                               // 偏航角 也就是摄像机左右的角度
//    camera.Pitch = 50.0f;                              // 俯仰角  也就是摄像机抬头或者低将头
    camera.MovementSpeed = 10000.0f;                    //摄像机 前进后退 左右移动的速度
    camera.MouseSensitivity = 0.1f;                  // 摄像机 视角旋转的灵敏度
    camera.Zoom = 45.0f;                               // 摄像机 拉进视角的快慢


}

opengl::~opengl()
{

}

void opengl::timeout()
{
    for (auto i=0;i< 50 ; i++ ) {
      nbody::update(data,nbody::DT);
    }

    update();//用于触发 paintGL
}

void opengl::startSimulation()
{
    qDebug() << "startSimulation";
    timer->start();
}

void opengl::stopSimulation()
{
    timer->stop();
}

void opengl::resetSimulation()
{
    data=nbody::testdata;
    timer->stop();

    update();
}

void opengl::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.2f,0.2f,0.25f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓存
}

void opengl::resizeGL(int w, int h)
{
}

void opengl::paintGL()
{
    //透视
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera.Zoom, (float)width()/height(),1,100000);

    //模型视角
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    QVector3D eye = camera.Position;
    QVector3D center = camera.Position+camera.Front;
    QVector3D up = camera.Up;
    GLdouble eyeX = eye.x();
    GLdouble eyeY = eye.y();
    GLdouble eyeZ = eye.z();
    GLdouble centerX = center.x();
    GLdouble centerY = center.y();
    GLdouble centerZ = center.z();
    GLdouble upX = up.x();
    GLdouble upY = up.y();
    GLdouble upZ = up.z();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);


    //绘制图形
    drawGrid(1400,10);
    paintAster(data);

//    glFlush(将);


}

void opengl::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
      case Qt::Key_Up :   camera.ProcessKeyboard(UP, deltaTime);break;
      case Qt::Key_Down : camera.ProcessKeyboard(DOWN,deltaTime);break;
      case Qt::Key_Right :camera.ProcessKeyboard(RIGHT,   deltaTime);break;
      case Qt::Key_Left : camera.ProcessKeyboard(LEFT,    deltaTime);break;
      case Qt::Key_W :    camera.ProcessKeyboard(UP, deltaTime);break;
      case Qt::Key_S :    camera.ProcessKeyboard(DOWN,deltaTime);break;
      case Qt::Key_A :    camera.ProcessKeyboard(LEFT,    deltaTime);break;
      case Qt::Key_D :    camera.ProcessKeyboard(RIGHT,   deltaTime);break;
      case Qt::Key_Q :    camera.ProcessKeyboard(FORWARD,   deltaTime);break;
      case Qt::Key_E :    camera.ProcessKeyboard(BACKWARD,   deltaTime);break;
    default:
        break;
    }

    update();

}


void opengl::mouseMoveEvent(QMouseEvent *event){
    currentPos = event->pos();
    deltaPos = currentPos - lastPos;
    lastPos = currentPos;

    camera.ProcessMouseMovement(deltaPos.x(), -deltaPos.y());
    update();
}

void opengl::mousePressEvent(QMouseEvent *event)
{
//  参考  https://blog.csdn.net/qq_40698750/article/details/122297176
//  解决鼠标点击的跳动
    currentPos = event->pos();
    lastPos = currentPos;
    update();
}


void opengl::wheelEvent(QWheelEvent *event)
{
    camera.ProcessMouseScroll(event->angleDelta().y()/120);
    update();
}



void opengl::paintStar(GLfloat x, GLfloat y, GLfloat z){


            // 定义太阳光源，它是一种白色的光源
            GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f}; //光源的位置在世界坐标系圆心，齐次坐标形式
            GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f}; //RGBA模式的环境光，为0
            GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f}; //RGBA模式的漫反射光，全白光
            GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  //RGBA模式下的镜面光 ，全白光
            glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
            glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

            //开启灯光
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHTING);
            glEnable(GL_DEPTH_TEST);

            // 定义太阳的材质并绘制太阳
            GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的环境光颜色，为0
            GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的漫反射光颜色，为0
            GLfloat sun_mat_specular[] = {1.0f, 1.0f, 0.5f, 1.0f};   //定义材质的镜面反射光颜色，为0
            GLfloat sun_mat_emission[] = {1.0f, 1.0f, 0.6f, 1.0f};   //定义材质的辐射广颜色，为偏红色
            GLfloat sun_mat_shininess   = 0.0f;

            glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);
            glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
            glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);


            glTranslatef(x, y, z);
            glutSolidSphere(100.0, 40, 32);
            glTranslatef(-x,-y,-z); //复位


}

void opengl::paintPlanet(GLfloat x, GLfloat y, GLfloat z)
{
        GLfloat earth_mat_ambient[]   = {1.0f, 1.0f, 1.0f, 0.5f};  //定义材质的环境光颜色，蓝色
        GLfloat earth_mat_diffuse[]   = {0.5f, 0.5f, 0.5f, 1.0f};  //定义材质的漫反射光颜色，蓝色
        GLfloat earth_mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};   //定义材质的镜面反射光颜色，红色
        GLfloat earth_mat_emission[] = {.2f, .2f, .5f, 1.0f};   //定义材质的辐射光颜色，为0
        GLfloat earth_mat_shininess   = 30.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
//        glRotatef(0, 0.0f, -1.0f, 0.0f);

//        glLoadIdentity();
        glTranslatef(x, y, z);
        glutSolidSphere(30.0, 40, 32);
        glTranslatef(-x,-y,-z); //复位

}


void opengl::paintAster(std::vector<Point> & v){
    for(auto it = v.begin(); it!=v.begin()+1;it++){
        paintStar(it->x,it->y,it->z);
    }
    for(auto it = v.begin()+1; it!=v.end();it++){
        paintPlanet(it->x,it->y,it->z);
    }
}

void opengl::drawGrid(qreal size, int nbSubdivisions)
{
    GLboolean lighting;
    glGetBooleanv(GL_LIGHTING, &lighting);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    for (int i = 0; i <= nbSubdivisions; ++i) {
        const float pos = size * (2.0 * i / nbSubdivisions - 1.0);
//        glVertex2d(pos, -size);
//        glVertex2d(pos, +size);
//        glVertex2d(-size, pos);
//        glVertex2d(size, pos);y

        // z = 0 x-y平面
        glVertex3d(pos, -size, 0);
        glVertex3d(pos, size, 0);
        glVertex3d(-size,pos, 0);
        glVertex3d(size,pos, 0);

//        // z = -size x-y平面
//        glVertex3d(pos, -size, -size);
//        glVertex3d(pos, size, -size);
//        glVertex3d(-size,pos, -size);
//        glVertex3d(size,pos, -size);

//        // x= -size z-y 平面
//        glVertex3d(-size,pos, -size);
//        glVertex3d(-size,pos, size);
//        glVertex3d(-size,-size,pos);
//        glVertex3d(-size,size,pos);

//        // x= size z-y 平面
//        glVertex3d(size,pos, -size);
//        glVertex3d(size,pos, size);
//        glVertex3d(size,-size,pos);
//        glVertex3d(size,size,pos);

//        // y= -size x-z 平面
//        glVertex3d(pos,size, -size);
//        glVertex3d(pos, size,size);
//        glVertex3d(-size,size,pos);
//        glVertex3d(size,size,pos);
    }
    glEnd();
    if (lighting)
        glEnable(GL_LIGHTING);
}
