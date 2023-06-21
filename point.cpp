#include "point.h"
#include<iostream>
#include<cstdio>
#include<cmath>
#include<fstream>
#include<iomanip>

void Point::print()
{
    printf(
            "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
            x, y, z,
            vx, vy, vz,
            ax, ay, az,
            m
          );
    std::fflush(stdout);//立即刷新缓冲区

}


std::istream & operator>>(std::istream & in, Point & p){
    in >> p.x >> p.y >> p.z >> p.vx >> p.vy >> p.vz >> p.ax >> p.ay >> p.az >> p.m;
    return in;
}
std::ostream & operator<<(std::ostream & out, Point & p){
    out.setf(std::ios::fixed);
    out.precision(6);
    out << p.x << " " << p.y << " " <<p.z << " " <<p.vx << " " <<p.vy << " " <<p.vz << " " <<p.ax << " " <<p.ay << " " <<p.az << " " <<p.m <<"\n";
    return out;
}
