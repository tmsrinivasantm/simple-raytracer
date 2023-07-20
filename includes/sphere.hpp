#pragma once
#include<point.hpp>
#include<hit.hpp>
#include<material.hpp>
namespace raytracer{
    class Sphere: public Hittable{
        public:
        Sphere(): center(Point()),radius(0.0){}
        Sphere(Point center, double radius, std::shared_ptr<material> ptr): center(center), radius(radius), matptr(ptr){}

        inline Point getCenter() const{return center;}
        inline double getRadius() const{return radius;}

        inline void setCenter(Point arg){ center = arg;}
        inline void setRadius(double arg){ radius = arg;}

        virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;
        



        private:
        Point center;
        double radius;
        std::shared_ptr<material> matptr;
    };
}