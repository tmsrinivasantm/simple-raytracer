#include<hit.hpp>

namespace raytracer{
    bool Hittable_list::hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const{
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(ray, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
    }
}