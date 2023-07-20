#include<sphere.hpp>

namespace raytracer{

    bool Sphere::hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
        Vec3 oc = ray.getOrigin() - center;
        double a = ray.getDirection().length_squared();
        double half_b = dot(ray.getDirection(), oc);
        double c = oc.length_squared() - (radius*radius);

        double discriminant = (half_b * half_b) - (a*c);

        if( discriminant < 0.0 )
            return false;
        
        double root = (-half_b - sqrt(discriminant)) / a;

        if(root < t_min || root > t_max){
            root = (-half_b + sqrt(discriminant)) / a;
            if(root < t_min || root > t_max)
                return false;
        }

        rec.t = root;
        rec.p = ray.at(rec.t);
        Point normal = (rec.p - center) / radius;
        rec.set_face(ray, normal);
        rec.matptr = matptr;

        return true;
        
    }
}