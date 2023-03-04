#include "nbodycalculate.h"
#include<constant.h>

/*calculating Euclid distance between two particles*/
double nbody::dist(const Point & particle1,const Point & particle2)
{
    return sqrt(
            (particle1.x - particle2.x) * (particle1.x - particle2.x) +
            (particle1.y - particle2.y) * (particle1.y - particle2.y) +
            (particle1.z - particle2.z) * (particle1.z - particle2.z));
}

/*update accelaration*/
void nbody::accelaration_update(std::vector<Point>& v)
{
    for (int j = 0; j < v.size(); ++j) {
        Point particle = v[j];
        Point p;
        int particle_index = j;
        double ax = 0;
        double ay = 0;
        double az = 0;
        double m = 0;
        double x;
        double y;
        double z;
        double r;
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

/*update velocity*/
void nbody::velocity_update(std::vector<Point>& v, double dt)
{
    for (auto  it = v.begin(); it != v.end(); ++it) {
        it->vx = it->ax * dt + it->vx;
        it->vy = it->ay * dt + it->vy;
        it->vz = it->az * dt + it->vz;
    }
}

/*update position*/
void nbody::position_update(std::vector<Point>&v, double dt)
{
    for (auto it = v.begin(); it != v.end(); ++it) {
        it->x = it->vx * dt + it->x;
        it->y = it->vy * dt + it->y;
        it->z = it->vz * dt + it->z;
    }
}

void nbody::update(std::vector<Point> &v,double dt)
{
    accelaration_update(v);
    velocity_update(v, dt);
    position_update(v, dt);
}
