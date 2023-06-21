#ifndef NBODYCALCULATE_H
#define NBODYCALCULATE_H

#include<point.h>
#include<vector>
#include<cmath>
#include<istream>
#include<map>

namespace nbody {

const float DT = 0.01;
const float MIN_DIST = 50;
inline std::vector<Point> testdata{
{0,0,0,0,0,0,0,0,0,100000},
{700,0,0,0,20,0,0,0,0,40},
{800,0,0,0,20,0,0,0,0,50},
{900,0,0,0,20,0,0,0,0,60},
{1100,0,0,0,21,0,0,0,0,70},
{1300,0,0,0,13,0,0,0,0,50},
{1500,0,0,0,15,0,0,0,0,50},
{1700,0,0,0,10,0,0,0,0,50},

};

/*calculating Euclid distance between two particles*/

float rsqrt(float number) ;
float dist(const Point & particle1,const Point &particle2);
float rdist(const Point & particle1,const Point & particle2);

/*update accelaration*/
void accelaration_update(std::vector<Point> & v);


/*update velocity*/
void velocity_update(std::vector<Point>& v, float dt);


/*update position*/
void position_update(std::vector<Point>&v,float dt);


void update(std::vector<Point> &v,float dt);

void read_data(std::vector<Point>&v, std::ifstream &ifs);

}

#endif // NBODYCALCULATE_H
