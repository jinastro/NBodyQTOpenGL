#ifndef POINT_H
#define POINT_H

struct Point
{
    Point(double x = 0,double y= 0,double z= 0,double vx= 0,double vy= 0,double vz= 0,double ax= 0,double ay= 0,double az= 0,double m= 0):x(x),y(y),z(z),vx(vx),vy(vy),vz(vz),ax(ax),ay(ay),az(az),m(m){};
    double x,y,z,vx,vy,vz,ax,ay,az,m;
    void print();
};

#endif // POINT_H
