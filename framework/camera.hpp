#ifndef CAMERA_HPP
#define CAMERA_HPP
#define _USE_MATH_DEFINES
#include<cmath>
#include<math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
#include"ray.hpp"
#include"light.hpp"
#include<glm/vec3.hpp>
#include<glm/glm.hpp>
#include<iostream>

#include<string>

#define corecrt_math_defines


struct Camera
{
public:
    std::string name_ = { "default Camera_name" };
    glm::vec3 origin_ = { 0,0,0 };
    glm::vec3 position_ = { 0,0,0 };
    float angle_ = { 0.0f };


    Ray shootRay(float x, float y, float width_, float height_) const
    {
        glm::vec3 rayOrigin{ 0,0,0 };
        glm::vec3 rayDirection = glm::normalize(glm::vec3{ (x - width_ / 2.0f), (y - height_ / 2.0f), -(width_ / 2) / tan(angle_ / 2 * (M_PI) / 180) });

        return Ray{ rayOrigin,rayDirection };
    }
  

    friend std::ostream& operator<< (std::ostream& os, Camera const& c) 
    {
        os << "Camera Name: " << c.name_ << " "
            << "Position: " << c.position_.x << ", " << c.position_.y << ", " << c.position_.z <<" "
            << "Camera Angle: " << c.angle_ <<std::endl;
        return os;
    }

};


#endif //CAMERA_HPP