#include<m_dielectric.hpp>

namespace raytracer{
    
    bool dielectric::scatter(const Ray& in,  Ray& scattered, Colour& attenuation, HitRecord& rec) const {
        double ir = rec.front_face?(1.0/refractive_index) : refractive_index;
        Vec3 incident_ray = unit_vector(in.getDirection());
        double cos_theta = fmin(dot(incident_ray, rec.normal),1.0);
        double sin_theta = sqrt(fabs(1-(cos_theta*cos_theta)));
        Vec3 out;
        if(ir * sin_theta < 1.0 || reflectance(cos_theta, ir) < random())
             out = get_refracted_ray(incident_ray, rec.normal, ir);
        else
             out = reflect(incident_ray, rec.normal);
        scattered = Ray(rec.p, out);
        attenuation = Colour(0.8,0.8,0.8);
        return true;        
    }
    
    double dielectric::reflectance(double cos, double ir) const {
        double r0 = (1-ir)/(1+ir);
        r0 = r0*r0;
        return r0 + (1-r0)*pow(cos,5.0);
    }
}