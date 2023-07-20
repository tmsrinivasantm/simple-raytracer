#pragma once
#include<limits>
#include<cstdlib>

namespace raytracer{
    //constants
    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    //utilities functions
    inline double degrees_to_radians(double degrees){
        return degrees * pi/180.0;
    }

    inline double random(){
        return rand() / (RAND_MAX + 1.0);
    }

    inline double random(double min, double max){
        return (min + (max-min)*random());
    }

    inline double clamp(double min, double max, double val){
        if(val < min)
            return min;
        else if( val > max)
            return max;
        return val;
    }
}

