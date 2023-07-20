#pragma once
#include<material.hpp>
namespace raytracer{
    class lambertian: public material{
        public:
       lambertian(Colour a):albedo(a){} 
       virtual bool scatter(const Ray& in,  Ray& scattered, Colour& attenuation, HitRecord& rec) const override;

       Colour albedo;  
    };
}