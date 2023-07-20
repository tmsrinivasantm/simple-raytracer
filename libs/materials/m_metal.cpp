#include<m_metal.hpp>

namespace raytracer{
    bool metal::scatter(const Ray& in, Ray& scattered, Colour& attenuation, HitRecord& rec) const {
        Point target = reflect(unit_vector(in.getDirection()), rec.normal);
        target = target + fuzz*unit_vector(random_unit_sphere());
        scattered = Ray(rec.p, target);
        attenuation = albedo;
        return (dot(target, rec.normal) > 0);
    }; 
}