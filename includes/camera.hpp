#pragma once
#include<vec3.hpp>
#include<point.hpp>
#include<ray.hpp>
namespace raytracer{
    class Camera{
        public:

        Camera(Point lookfrom, Point lookat, Point vup, double vfov, double aspect_ratio){
            Point w = unit_vector(lookfrom - lookat);
            Point u = unit_vector(cross(vup, w));
            Point v = cross(w,u);
            auto h = tan(degrees_to_radians(vfov)/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;
        }

        Ray get_ray(double s, double t){
            return Ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
        }

        private:
        Point origin;
        Vec3 horizontal;
        Vec3 vertical;
        Point lower_left_corner;
    };
}