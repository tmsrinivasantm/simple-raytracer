#include<m_lambertian.hpp>

namespace raytracer{
 bool lambertian::scatter(const Ray& in,  Ray& scattered, Colour& attenuation, HitRecord& rec) const {
      Point target = rec.normal + unit_vector(random_unit_sphere());
      if(target.near_zero()){
        target = rec.normal;
      }
      scattered = Ray(rec.p, target); 
      attenuation = albedo; 
      return true;
    
    }
}