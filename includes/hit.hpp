#pragma once
#include<point.hpp>
#include<ray.hpp>
#include<vector>
#include<memory>
namespace raytracer{

    class material; // just a hint to the compiler that a class named material exists
    struct HitRecord{
        double t;
        Vec3 normal;
        Point p;
        bool front_face;
        std::shared_ptr<material> matptr;
        inline void set_face(const Ray& ray, const Point& outward_normal){
            front_face = dot(ray.getDirection(), outward_normal) < 0;
            normal = front_face ? outward_normal :(-1 * outward_normal);
        }
    };

    class Hittable{
        public:
        virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const = 0;

    };

    class Hittable_list:public Hittable{
        public:
        Hittable_list(){}

        inline void add(std::shared_ptr<Hittable> arg){objects.push_back(arg);}

        inline void remove(){objects.pop_back();}

        virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;

        inline std::shared_ptr<Hittable> getFirst() const { return objects[0]; }
        

        
        private:
        std::vector<std::shared_ptr<Hittable>> objects;
    };
}