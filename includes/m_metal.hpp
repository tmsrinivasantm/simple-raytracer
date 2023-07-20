#pragma once
#include<material.hpp>
namespace raytracer{
    class metal: public material{
        public:
       metal(Colour a, double f): albedo(a), fuzz(f < 1 ? f : 1 ) {}
       virtual bool scatter(const Ray& in, Ray& scattered, Colour& attenuation, HitRecord& rec) const override;

       Colour albedo;  
       double fuzz;
    };
}