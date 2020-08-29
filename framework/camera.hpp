#ifndef CAMERA_HPP
#define CAMERA_HPP
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
#include "ray.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>


struct Camera
{
    std::string name_ = { "default Camera_name" };
    glm::vec3 origin_ = { 0,0,0 };
    glm::vec3 position_ = { 0,0,0 };
    float angle_ = { 0.0f };



    Ray shoot_ray(float x, float y, float width_, float height_) const {
        glm::vec3 rayOrigin{ 0,0,0 };
        glm::vec3 rayDirection = glm::normalize(glm::vec3{ (x-width_/2.0f), (y-height_/2.0f), -(width_/2)/tan(angle_/2*M_PI/180) });
        // cout<<rayDirection.x<<" "<<rayDirection.y<<" "<<rayDirection.z<<endl;
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