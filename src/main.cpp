#include <iostream>
#include<thread>
#include<mutex>

//local includes
#include<colour.hpp>
#include<ray.hpp>
#include<sphere.hpp>
#include<raytracer.hpp>
#include<camera.hpp>
#include<m_lambertian.hpp>
#include<m_metal.hpp>
#include<m_dielectric.hpp>

raytracer::Colour ray_colour(const raytracer::Ray& ray, const raytracer::Hittable_list& world, int depth){

    raytracer::HitRecord rec{};

    if(depth == 0) return raytracer::Colour(0,0,0);

    if(world.hit(ray, 0.001, raytracer::infinity, rec)){
        raytracer::Ray scattered;
        raytracer::Colour attenuation;
        if(rec.matptr->scatter(ray,scattered, attenuation, rec)){
            return attenuation * ray_colour(scattered, world, depth -1);
        }
        return raytracer::Colour();
    }

    raytracer::Vec3 direction = raytracer::unit_vector(ray.getDirection());

    double t = 0.5*(direction.y() + 1.0);

    return (1.0-t) * raytracer::Colour(1.0,1.0,1.0) + t * raytracer::Colour(0.5,0.7,1.0);

}

raytracer::Hittable_list random_scene() {
   raytracer::Hittable_list world;

    auto ground_material = std::make_shared<raytracer::lambertian>(raytracer::Colour(0.5, 0.5, 0.5));
    world.add(std::make_shared<raytracer::Sphere>(raytracer::Point(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = raytracer::random();
            raytracer::Point center(a + 0.9*raytracer::random(), 0.2, b + 0.9*raytracer::random());

            if ((center - raytracer::Point(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<raytracer::material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = raytracer::Colour::random_box() * raytracer::Colour::random_box();
                    sphere_material = std::make_shared<raytracer::lambertian>(albedo);
                    world.add(std::make_shared<raytracer::Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = raytracer::Colour::random_box(0.5, 1);
                    auto fuzz = raytracer::random(0, 0.5);
                    sphere_material = std::make_shared<raytracer::metal>(albedo, fuzz);
                    world.add(std::make_shared<raytracer::Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<raytracer::dielectric>(1.5);
                    world.add(std::make_shared<raytracer::Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<raytracer::dielectric>(1.5);
    world.add(std::make_shared<raytracer::Sphere>(raytracer::Point(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<raytracer::lambertian>(raytracer::Colour(0.4, 0.2, 0.1));
    world.add(std::make_shared<raytracer::Sphere>(raytracer::Point(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<raytracer::metal>(raytracer::Colour(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<raytracer::Sphere>(raytracer::Point(4, 1, 0), 1.0, material3));

    return world;
}

int main() {

    // Image
    const double aspect_ratio = 3.0/2.0;
    const int image_width = 256;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const double samples_per_pixel = 100.0;

    //world
    raytracer::Hittable_list world = random_scene();
    // Camera
    raytracer::Camera camera(raytracer::Point(13,2,3),raytracer::Point(0,0,0),raytracer::Point(0,1,0),20.0,aspect_ratio);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    int i=0;
    int j=0;
    std::mutex mut;
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
        std::cerr<<"\rScan lines remaining "<<' '<<j<<std::flush;
            std::vector<std::thread> threads;                                
            raytracer::Colour pixel_color = raytracer::Colour(); 
            const auto lambda = [&mut, &camera, i, j, &world, &pixel_color, &image_height, &image_width]() {
                    auto u = (i + raytracer::random()) / (image_width-1);
                    auto v = (j + raytracer::random()) / (image_height-1);
                    raytracer::Ray ray= camera.get_ray(u,v);
                    raytracer::Colour out_colour = ray_colour(ray,world,50);
                    mut.lock();
                    pixel_color = pixel_color + out_colour;
                    mut.unlock();
            };
            for(int k=0; k<samples_per_pixel; k++){
                threads.push_back(std::thread(lambda));
            }
            for(int k=0;k<threads.size();k++){
                threads.at(k).join();
            }
            raytracer::write_colour(pixel_color, samples_per_pixel, 2.0);
        }
    }
}