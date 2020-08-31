#ifndef LIGHT_HPP
#define LIGHT_HPP
#include "color.hpp"
#include <iostream>
#include<glm/vec3.hpp>

struct Light
{
	std::string name_ = "defalut light";
	Color color_{ 0.0f, 0.0f, 0.0f };
	glm::vec3 position_{ 0.0,0.0,0.0 };
	unsigned int brightness_{0};

	friend std::ostream& operator<< (std::ostream& os, Light const& l)
	{
		os << "Light Name: " << l.name_ <<" "
			<< "Color: " << l.color_.r << ", " << l.color_.g << ", " << l.color_.b << " "
			<< "Position: " << l.position_.x << ", " << l.position_.y << ", " << l.position_.z << " "
			<< "Brightness: " << l.brightness_ << std::endl;
		return os;
	}
};

#endif