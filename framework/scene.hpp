#ifndef SCENE_HPP
#define SCENE_HPP
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<map>
#include<set>
#include<vector>
#include<memory> //shared_ptr
#include<algorithm>
#include "camera.hpp"
#include"shape.hpp"
#include"material.hpp"
#include"light.hpp"

// um auf unseren material_ptr zu verweisen
using material_ptr = std::shared_ptr<Material>;
using shape_ptr = std::shared_ptr<Shape>;

struct Scene
{
	std::string name = "default scene_name";
	Camera camera;
	std::map<std::string, std::shared_ptr<Material>> material_map;
	std::vector<std::shared_ptr<Shape>> shape_vector;
	

};

Scene open_sdf(std::string const& sdf_name); // Der Rückgabetyp ist eine Scene


#endif