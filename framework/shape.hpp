#ifndef SHAPE_HPP
#define SHAPE_HPP 
#include <glm/vec3.hpp>
#include "material.hpp"
//#include "hit.hpp"
//#include "ray.hpp"
#include <string> // std::string 
#include <iostream> 
#include <memory> // shared_ptr
#include "hit.hpp"
#include "ray.hpp"

class Shape
{

public:
    Shape();
    Shape(std::shared_ptr<Material> const& material, std::string const& name);

  //  virtual float area() const = 0; //hier wird noch nicht implementiert
  //  virtual float volume() const = 0; //wir k�nnen kein statisches/dynamisches Objekt von Shape anlegen sondern nur ein Pointer/Referenz
    virtual std::shared_ptr<Hit> intersect(Ray const& ray) const = 0;



    //virtual 
    ~Shape(); //Destruktor

    virtual std::ostream& print(std::ostream& os) const;


    //private:
    //Mit getter und Aufruf
    std::shared_ptr<Material> m_;
    std::string name_;


};


std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif 