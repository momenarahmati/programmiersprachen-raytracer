#include "box.hpp"
#include "ebene.hpp"
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

std::shared_ptr<Hit> Box::intersect(Ray const& ray) const {

    Ebene ebene1{ min_, glm::vec3 {-1,0,0} };
    Ebene ebene2{ min_, glm::vec3 {0,0,-1} };
    Ebene ebene3{ min_, glm::vec3 {0,-1,0} };
    Ebene ebene4{ max_, glm::vec3 {1,0,0} };
    Ebene ebene5{ max_, glm::vec3 {0,0,1} };
    Ebene ebene6{ max_, glm::vec3 {0,1,0} };

    float distance1 = (glm::dot(ebene1.normal, ebene1.origin) - glm::dot(ray.origin, ebene1.normal)) / (glm::dot(ray.direction, ebene1.normal));
    float distance2 = (glm::dot(ebene2.normal, ebene2.origin) - glm::dot(ray.origin, ebene2.normal)) / (glm::dot(ray.direction, ebene2.normal));
    float distance3 = (glm::dot(ebene3.normal, ebene3.origin) - glm::dot(ray.origin, ebene3.normal)) / (glm::dot(ray.direction, ebene3.normal));
    float distance4 = (glm::dot(ebene4.normal, ebene4.origin) - glm::dot(ray.origin, ebene4.normal)) / (glm::dot(ray.direction, ebene4.normal));
    float distance5 = (glm::dot(ebene5.normal, ebene5.origin) - glm::dot(ray.origin, ebene5.normal)) / (glm::dot(ray.direction, ebene5.normal));
    float distance6 = (glm::dot(ebene6.normal, ebene6.origin) - glm::dot(ray.origin, ebene6.normal)) / (glm::dot(ray.direction, ebene6.normal));

    std::vector<glm::vec3> hit_points;
    std::vector<glm::vec3> hit_normals;
    glm::vec3 cut_point;

	if (distance1 > 0) {
		cut_point = ray.origin + distance1 * ray.direction;
		if (cut_point.y <= max_.y && cut_point.y >= min_.y && cut_point.z <= max_.z && cut_point.z >= min_.z) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(ebene1.normal);
		}
	}
	if (distance4 > 0) {
		cut_point = ray.origin + distance4 * ray.direction;
		if (cut_point.y <= max_.y && cut_point.y >= min_.y && cut_point.z <= max_.z && cut_point.z >= min_.z) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(ebene4.normal);
		}
	}
	//untere Flaeche
	if (distance2 > 0) {
		cut_point = ray.origin + distance2 * ray.direction;
		if (cut_point.y <= max_.y && cut_point.y >= min_.y && cut_point.x <= max_.x && cut_point.x >= min_.x) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(ebene2.normal);
		}
	}
	//obere Flaeche
	if (distance5 > 0) {
		cut_point = ray.origin + distance5 * ray.direction;
		//std::cout << min_.x << " ; " << min_.y << " ; " << min_.z << "\n";
		if (cut_point.y <= max_.y && cut_point.y >= min_.y && cut_point.x <= max_.x && cut_point.x >= min_.x) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(ebene5.normal);
		}
	}
	if (distance3 > 0) {
		cut_point = ray.origin + distance3 * ray.direction;
		if (cut_point.x <= max_.x && cut_point.x >= min_.x && cut_point.z <= max_.z && cut_point.z >= min_.z) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(ebene3.normal);
		}
	}
	if (distance6 > 0) {
		cut_point = ray.origin + distance6 * ray.direction;
		if (cut_point.x <= max_.x && cut_point.x >= min_.x && cut_point.z <= max_.z && cut_point.z >= min_.z) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(ebene6.normal);
		}
	}

	//der Schnittpunkt der am naehesten an der Kamera ist nehmen
	if (hit_points.size() > 0) {
		glm::vec3 closest_hit = hit_points.at(0);
		glm::vec3 closest_normal = hit_normals.at(0);

		for (auto it = 0; it < hit_points.size(); ++it) {
			if (glm::length(hit_points.at(it) - ray.origin) < glm::length(closest_hit - ray.origin)) {
				closest_hit = hit_points.at(it);
				closest_normal = hit_normals.at(it);
			}
		}

		
		return std::make_shared <Hit>(Hit{ closest_hit, closest_normal });
	}
	return nullptr;
};