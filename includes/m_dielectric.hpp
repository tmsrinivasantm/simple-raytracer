#pragma once
#include<material.hpp>
#include<colour.hpp>

namespace raytracer{
    class dielectric : public material{
        public:
        dielectric(double r_i):refractive_index(r_i){}

       virtual bool scatter(const Ray& in,  Ray& scattered, Colour& attenuation, HitRecord& rec) const override;


        double refractive_index;
        
        private:
        double reflectance(double cos, double ir) const;
        
    };
}