#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "ray.hpp"
#include "shape.hpp"
#include "hit.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape
{
public:

    //Konstruktoren
    Sphere();
    Sphere(glm::vec3 const& center, float radius);
    Sphere(std::shared_ptr<Material> const& material, std::string const& name, glm::vec3 const& center, float radius);

    ~Sphere();

    //get-Methoden
    glm::vec3 get_center() const;
    float get_radius() const;


    //virtuelle Methoden aus Shape
  //  float area() const override;
   // float volume() const override;

    std::ostream& print(std::ostream& os) const override;

     std::shared_ptr<Hit> intersect(Ray const& ray) const; //per referenz schon sinnvoll

     //private: 
    glm::vec3 center_;
    float radius_;

};

std::ostream& operator<< (std::ostream& os, Sphere const& s);


#endif //SPHERE_HPP