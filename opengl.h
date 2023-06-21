#ifndef OPENGL_H
#define OPENGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include<QOpenGLShaderProgram>
#include<QOpenGLShader>
#include<QTimer>
#include<QTime>
#include<QKeyEvent>
#include<QWheelEvent>
#include<camera.h>
#include<nbodycalculate.h>


#include<point.h>

class opengl : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit opengl(QWidget *parent = nullptr);
    ~opengl();

    std::vector<Point> init_data;
    std::vector<Point> data;
    void startSimulation();
    void stopSimulation();
    void resetSimulation();

    void paintStar(GLfloat x, GLfloat y, GLfloat z, GLfloat size);
    void paintPlanet(GLfloat x, GLfloat y, GLfloat z, GLfloat size);
    void paintAster(std::vector<Point> & v);
    void paintSolarSystem(std::vector<Point> & v);
    void paintPoints(std::vector<Point> &v);
    void drawGrid(qreal size, int nbSubdivisions);
    void camera_init();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent * event);
    virtual void mousePressEvent(QMouseEvent *event);


public slots:
    void timeout();

private:

    //时间变量
    QTimer * timer = new QTimer(this);

    //摄像机及其相关变量
    Camera camera;
    const float TIMEOUTMSEC = 100;
    const float deltaTime = TIMEOUTMSEC/10000;//控制键盘移动视角的平滑程度

    QPoint deltaPos;
    QPoint lastPos;
    QPoint currentPos;

signals:

};

#endif // OPENGL_H
