#include<ray.hpp>

namespace raytracer{
    Ray::Ray(){
        origin = Point();
        direction = Vec3();
    }
    Ray::Ray(const Point& origin, const Vec3& direction){
        this->origin = origin;
        this->direction = direction;
    }
    
}