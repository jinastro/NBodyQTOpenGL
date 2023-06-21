#ifndef POINT_H
#define POINT_H

#include<iostream>

struct Point
{
    Point(float x = 0,float y= 0,float z= 0,float vx= 0,float vy= 0,float vz= 0,float ax= 0,float ay= 0,float az= 0,float m= 0):x(x),y(y),z(z),vx(vx),vy(vy),vz(vz),ax(ax),ay(ay),az(az),m(m){};
    float x,y,z,vx,vy,vz,ax,ay,az,m;
    void print();
};

std::istream & operator>>(std::istream & is, Point & p);
std::ostream & operator<<(std::ostream & out, Point & p);

#endif // POINT_H
