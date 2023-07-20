#pragma once
#include<colour.hpp>
#include<hit.hpp>
#include<point.hpp>
#include<ray.hpp>
namespace raytracer{
    class material{
       public:
       virtual bool scatter(const Ray& in,  Ray& scattered, Colour& attenuation, HitRecord& rec) const = 0;

    };
}