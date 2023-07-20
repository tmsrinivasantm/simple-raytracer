#pragma once
#include<point.hpp>

namespace raytracer{
    class Ray{
        public:
        Ray();
        Ray(const Point& origin, const Vec3& direction);
        inline Point at(double t) const { return (origin + t*direction); }
        inline Vec3 getDirection() const{ return direction;}
        inline Point getOrigin() const { return origin; }
        private:
        Point origin;
        Vec3 direction;
    };
}