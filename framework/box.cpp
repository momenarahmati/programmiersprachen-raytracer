#include "box.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp> 
#include <vector>
#include <iostream>
#include <limits> // numeric_limits 
using namespace std;

//Konstruktoren 

Box::Box() :
    Shape(),
    min_{ 0.0f, 0.0f, 0.0f },
    max_{ 1.0f, 1.0f, 1.0f }
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
    Shape(),
    min_{ min },
    max_{ max }
{}

Box::Box(std::shared_ptr<Material> const& material, std::string const& name, glm::vec3 const& min, glm::vec3 const& max) :
    Shape(material, name),
    min_{ min },
    max_{ max }
{}

//Box::~Box() {}


glm::vec3 Box::get_min() const
{
    return min_;
}

glm::vec3 Box::get_max() const
{
    return max_;
}
/*
float Box::area() const
{
    float length = max_.x - min_.x;
    float heigth = max_.y - min_.y;
    float width = max_.z - min_.z;
    return 2 * (length * heigth) + 2 * (length * width) + 2 * (heigth * width);
}

float Box::volume() const
{
    float length = max_.x - min_.x;
    float heigth = max_.y - min_.y;
    float width = max_.z - min_.z;
    return length * heigth * width;
}
*/

std::ostream& operator<< (std::ostream& os, const Box& b)
{
    return b.print(os);
}


std::ostream& Box::print(std::ostream& os) const
{
    Shape::print(os);
    os
        << "Position_Minimum: " << min_.x << "," << min_.y << min_.z << "\n"
        << "Position_Maximum: " << max_.x << "," << max_.y << max_.z << "\n";
    return os;
}