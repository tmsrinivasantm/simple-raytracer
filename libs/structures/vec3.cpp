#include<vec3.hpp>

namespace raytracer{
    Vec3::Vec3(){
        e[0] = e[1] = e[2] = 0;    
    }

    Vec3::Vec3(double a, double b, double c){
        e[0] = a;
        e[1] = b;
        e[2] = c;  
    }
    
    double Vec3::dot(const Vec3& vec){
        return e[0] * vec.e[0] + e[1] * vec.e[1] + e[2] * vec.e[2];
    }

    Vec3 Vec3::cross(const Vec3& vec){
            return Vec3(e[1] * vec.e[2] - e[2] * vec.e[1],
                e[2] * vec.e[0] - e[0] * vec.e[2],
                e[0] * vec.e[1] - e[1] * vec.e[0]);
    }

    double Vec3::length(){
        return std::sqrt(length_squared());
    }

    double Vec3::length_squared(){
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
}