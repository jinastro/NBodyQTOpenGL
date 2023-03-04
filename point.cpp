#include "point.h"
#include<iostream>
#include<cstdio>
#include<cmath>

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
