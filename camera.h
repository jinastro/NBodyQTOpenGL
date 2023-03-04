#ifndef CAMERA_H
#define CAMERA_H

#include<QMatrix4x4>
#include<vector>
#include<GL/gl.h>


// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
//const float YAW         = -90.0f; // 偏航角 也就是摄像机左右的角度
//const float PITCH       =  0.0f; // 俯仰角  也就是摄像机抬头或者低将头
//const float SPEED       =  2.5f;//摄像机 前进后退 左右移动的速度
//const float SENSITIVITY =  0.1f;// 摄像机 视角旋转的灵敏度
//const float ZOOM        =  45.0f;// 摄像机 拉进视角的快慢
const float YAW         = -90.0f; // 偏航角 也就是摄像机左右的角度
const float PITCH       =  50.0f; // 俯仰角  也就是摄像机抬头或者低将头 不知道为什么 设置为 0.0 会无法绘制第一张图
const float SPEED       =  2.5f;//摄像机 前进后退 左右移动的速度
const float SENSITIVITY =  0.1f;// 摄像机 视角旋转的灵敏度
const float ZOOM        =  45.0f;// 摄像机 拉进视角的快慢

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    QVector3D Position;
    QVector3D Front;
    QVector3D Up;
    QVector3D Right;
    QVector3D WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(QVector3D position = QVector3D(0.0f, 0.0f, 0.0f), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = QVector3D(posX, posY, posZ);
        WorldUp = QVector3D(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    QMatrix4x4 GetViewMatrix()
    {
        QMatrix4x4 matrix;
        matrix.lookAt(Position, Position + Front, Up);
        return matrix;
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
        if (direction == UP)
            Position += Up * velocity;
        if (direction == DOWN)
            Position -= Up * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // 这部分改动较多
    double radians(float degree){
       const float PI = 3.1415926;
       return degree*PI/180.0;
    }
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        QVector3D front;
        front.setX(cos(radians(Yaw)) * cos(radians(Pitch)));
        front.setY(sin(radians(Pitch)));
        front.setZ(sin(radians(Yaw)) * cos(radians(Pitch)));
        front.normalize();
        Front = front;
        // also re-calculate the Right and Up vector
        Right = QVector3D::crossProduct(Front,WorldUp);
        Right.normalize();
        Up = QVector3D::crossProduct(Right,Front);
        Up.normalize();
    }
};

#endif // CAMERA_H
