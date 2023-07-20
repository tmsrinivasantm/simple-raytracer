#pragma once
#include<iostream>
#include<cmath>
#include<raytracer.hpp>

namespace raytracer{
    class Vec3{
        public:
        Vec3();
        Vec3(double a, double b, double c);

        std::ostream& operator<<(const Vec3& rhs);

        double operator [](size_t index);

        double dot(const Vec3& vec);
        Vec3 cross(const Vec3& vec);
        double length();
        double length_squared();

        inline double x() const{return e[0];};
        inline double y() const{return e[1];};
        inline double z() const{return e[2];};

        inline static Vec3 random_box(double min, double max) { 
            return Vec3(random(min, max), 
                        random(min, max), 
                        random(min, max)
                        );
        }

        inline static Vec3 random_box(){
            return Vec3(
                random(),
                random(),
                random()
            );
        }

        inline bool near_zero(){
            auto s = 1e-8;
            return ((e[0] < s) && (e[1] < s) && (e[2] < s));
        }


        double e[3];
        
    };

    
    inline Vec3 random_unit_sphere(){
        while(true){
            Vec3 p = Vec3::random_box(-1,1);
            if(p.length_squared()>=1) continue;
            return p;
        }
    }

    inline Vec3 operator *=(const double& t, const Vec3& v){
        return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
    }
    inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
        return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
        return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
        return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    inline Vec3 operator*(double t, const Vec3 &v) {
        return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
    }

    inline Vec3 operator*(const Vec3 &v, double t) {
        return t * v;
    }

    inline Vec3 operator/(Vec3 v, double t) {
        return (1/t) * v;
    }

    inline double dot(const Vec3 &u, const Vec3 &v) {
        return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
    }

    inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
        return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                    u.e[2] * v.e[0] - u.e[0] * v.e[2],
                    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    inline Vec3 unit_vector(Vec3 v) {
        return v / v.length();
    }

    inline Vec3 reflect(const Vec3& v, Vec3& n){
        return v - 2*dot(v,n)*n;
    }
    
    
    inline Vec3 get_refracted_ray(const Vec3& R, const Vec3& normal, double refractive_index){
        double cos_theta = dot(R, normal);
        auto perp = refractive_index*(R + -1 * cos_theta*normal);                
        auto parallel = -1 * sqrt(fabs(1.0 - perp.length_squared())) * normal;
        return perp + parallel;
        
    }
}