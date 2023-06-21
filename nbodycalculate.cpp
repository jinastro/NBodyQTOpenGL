#include "nbodycalculate.h"
#include<constant.h>

// 不知道为什么 ， 这个神奇的算法函数没算出来的值是负数 而且也不快。。。
float nbody::rsqrt(float number) {
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y = number;
  i = *(long *)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float *)&i;

  y = y * (threehalfs - (x2 * y * y));
  return y;
}

/*calculating Euclid distance between two particles*/
float nbody::dist(const Point & particle1,const Point & particle2)
{
//    std::cout << sqrt(
//                     (particle1.x - particle2.x) * (particle1.x - particle2.x) +
//                     (particle1.y - particle2.y) * (particle1.y - particle2.y) +
//                     (particle1.z - particle2.z) * (particle1.z - particle2.z))
//              << " "<< -1/rsqrt(
//                     (particle1.x - particle2.x) * (particle1.x - particle2.x) +
//                     (particle1.y - particle2.y) * (particle1.y - particle2.y) +
//                     (particle1.z - particle2.z) * (particle1.z - particle2.z))
//<< std::endl;
    return sqrt(
            (particle1.x - particle2.x) * (particle1.x - particle2.x) +
            (particle1.y - particle2.y) * (particle1.y - particle2.y) +
            (particle1.z - particle2.z) * (particle1.z - particle2.z));
}

float nbody::rdist(const Point & particle1,const Point & particle2)
{
    return -rsqrt(
            (particle1.x - particle2.x) * (particle1.x - particle2.x) +
            (particle1.y - particle2.y) * (particle1.y - particle2.y) +
            (particle1.z - particle2.z) * (particle1.z - particle2.z) + MIN_DIST);
}

/*update accelaration*/

void nbody::accelaration_update(std::vector<Point>& v)
{
    for (int j = 0; j < v.size(); ++j) {
        Point particle = v[j];
        Point p;
        int particle_index = j;
        float ax = 0;
        float ay = 0;
        float az = 0;
        float m = 0;
        float x;
        float y;
        float z;
        float r;
        for (int i = 0; i < particle_index; ++i) {
            p = v[i];
            x = p.x;
            y = p.y;
            z = p.z;
            m = p.m;
            r = dist(p, particle)+MIN_DIST;
            r = r * r * r;
            ax += constant::G * m * (x - particle.x) / r;
            ay += constant::G * m * (y - particle.y) / r;
            az += constant::G * m * (z - particle.z) / r;
        }
        for (int i = particle_index + 1; i < v.size(); ++i) {
            p = v[i];
            x = p.x;
            y = p.y;
            z = p.z;
            m = p.m;
            r = dist(p, particle)+MIN_DIST;
            r = r * r * r;
            ax += constant::G * m * (x - particle.x) / r;
            ay += constant::G * m * (y - particle.y) / r;
            az += constant::G * m * (z - particle.z) / r;
        }
        v[j].ax = ax;
        v[j].ay = ay;
        v[j].az = az;
    }
}

//void nbody::accelaration_update(std::vector<Point>& v)
//{
//    for (int j = 0; j < v.size(); ++j) {
//        Point particle = v[j];
//        Point p;
//        int particle_index = j;
//        float ax = 0;
//        float ay = 0;
//        float az = 0;
//        float m = 0;
//        float x;
//        float y;
//        float z;
//        float r;
//        for (int i = 0; i < particle_index; ++i) {
//            p = v[i];
//            x = p.x;
//            y = p.y;
//            z = p.z;
//            m = p.m;
//            r = rdist(p, particle);
//            r = r * r * r;
//            ax += constant::G * m * (x - particle.x) * r;
//            ay += constant::G * m * (y - particle.y) * r;
//            az += constant::G * m * (z - particle.z) * r;
//        }
//        for (int i = particle_index + 1; i < v.size(); ++i) {
//            p = v[i];
//            x = p.x;
//            y = p.y;
//            z = p.z;
//            m = p.m;
//            r = rdist(p, particle);
//            r = r * r * r;
//            ax += constant::G * m * (x - particle.x) * r;
//            ay += constant::G * m * (y - particle.y) * r;
//            az += constant::G * m * (z - particle.z) * r;
//        }
//        v[j].ax = ax;
//        v[j].ay = ay;
//        v[j].az = az;
//    }
//}

/*update velocity*/
void nbody::velocity_update(std::vector<Point>& v, float dt)
{
    for (auto  it = v.begin(); it != v.end(); ++it) {
        it->vx = it->ax * dt + it->vx;
        it->vy = it->ay * dt + it->vy;
        it->vz = it->az * dt + it->vz;
    }
}

/*update position*/
void nbody::position_update(std::vector<Point>&v, float dt)
{
    for (auto it = v.begin(); it != v.end(); ++it) {
        it->x = it->vx * dt + it->x;
        it->y = it->vy * dt + it->y;
        it->z = it->vz * dt + it->z;
    }
}

void nbody::update(std::vector<Point> &v,float dt)
{
    accelaration_update(v);
    velocity_update(v, dt);
    position_update(v, dt);
}


void nbody::read_data(std::vector<Point> &v, std::ifstream & ifs)
{
//    float point;
//    while(getline(ifs,d)){

//    }

}
