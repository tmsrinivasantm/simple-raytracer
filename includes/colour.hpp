#pragma once
#include<vec3.hpp>
#include<iostream>
#include<raytracer.hpp>

namespace raytracer{
    using Colour = Vec3;

    inline void write_colour(const Colour& pixel, const double& samples_per_pixel, double gamma){
        double scale = 1.0 / samples_per_pixel;

        double r = pixel.x();
        double g = pixel.y();
        double b = pixel.z();

        r*=scale;
        g*=scale;
        b*=scale;

        r = pow((clamp(0.0,0.999,r)), 1.0/gamma);
        g = pow((clamp(0.0,0.999,g)), 1.0/gamma);
        b = pow((clamp(0.0,0.999,b)), 1.0/gamma);

        std::cout<< static_cast<int>(255 * r)<< ' '
           << static_cast<int>(255 * g)<< ' '
           << static_cast<int>(255 * b)<< '\n';
    }
}