#include "scene.hpp"


Scene open_sdf(std::string const& sdf_name)
{
	std::ifstream dat_ein; // ifstram darf nur in der Datei lesen
	dat_ein.open(sdf_name);
	std::string buffer;

	while (std::getline(dat_ein, buffer))
	{
		std::stringstream line_stream(buffer);
		// liest die zeichen der Zeile als einzelne strings
		std::string class_name;

		line_stream >> class_name;
		if ("define" == class_name)
		{
			// Material einlesen
			line_stream >> class_name;
			if ("material" == class_name)
			{
				std::shared_ptr<Material> new_material_ptr = std::make_shared<Material>();
				//Objekt vom Typ shared pointer Material 
				line_stream >> new_material_ptr->name;
				//bei pointern dereferenzieren ->
				line_stream >> new_material_ptr->ka.r;
				line_stream >> new_material_ptr->ka.g;
				line_stream >> new_material_ptr->ka.b;
				line_stream >> new_material_ptr->kd.r;
				line_stream >> new_material_ptr->kd.g;
				line_stream >> new_material_ptr->kd.b;
				line_stream >> new_material_ptr->ks.r;
				line_stream >> new_material_ptr->ks.g;
				line_stream >> new_material_ptr->ks.b;
				line_stream >> new_material_ptr->m_exponent;
				//Hier wird jedes durch ein whitespace getrenntes string/float etc. (wird selbstständig interpretiert)
				//in den jeweiligen Variablen gespeichert 

				std::cout << *new_material_ptr << "\n";
				//Ausgabe auf der Konsole 

				(new_scene.material_map).insert(make_pair(new_material_ptr->name, new_material_ptr));
				//Speichern des neuen Materials in einer Map mit dem namen des Materials als key 
				//und einem pointer auf dieses Material als value 

				//SHAPE einlesen 
				if ("shape" == class_name)
				{
					line_stream >> class_name;

					if ("box" == class_name)
					{
						auto new_box_ptr = std::make_shared<Box>();

						line_stream >> new_box_ptr->name_;
						line_stream >> new_box_ptr->min_.x;
						line_stream >> new_box_ptr->min_.y;
						line_stream >> new_box_ptr->min_.z;
						line_stream >> new_box_ptr->max_.x;
						line_stream >> new_box_ptr->max_.y;
						line_stream >> new_box_ptr->max_.z;

						line_stream >> class_name;
						new_box_ptr->m_ = find_material(calss_name, new_scene.material_map);
						//das Material der Box wird in unserer Map gesucht 
						(new_scene.shape_vector).push_back(new_box_ptr);
						std::cout << *new_box_ptr << "\n";
					}

					if ("sphere" == class_name)
					{
						auto new_sphere_ptr = std::make_shared<Sphere>();

						line_stream >> new_sphere_ptr->name_;
						line_stream >> new_sphere_ptr->center_.x;
						line_stream >> new_sphere_ptr->center_.y;
						line_stream >> new_sphere_ptr->center_.z;
						line_stream >> new_sphere_ptr->radius_;

						line_stream >> class_name;
						new_sphere_ptr->m_ = find_material(class_name, new_scene.material_map);
						(new_scene.shape_vector).push_back(new_sphere_ptr);

						std::cout << *new_sphere_ptr << "\n";
					}

				}
			}
		}
	}
	dat_ein.close();
	return new_scene;
}

// find funktion für die Map Material
material_ptr find_material(std::string const& eingabe, std::map<std::string, std::shared_ptr<Material>> const& material_map)
{
	auto it = material_map.find(eingabe);
	//Variable it geht durch die Map und sucht nach Eingabe 
	if (it != material_map.end())
	{
		std::cout << "Material " << eingabe << " exists." << endl;
		return it->second;
		//first ist key, second ist value  
	}
	else
	{
		std::cout << "Material " << eingabe << " doesn't exists." << endl;
		return nullptr;
	}
}

//Find Funktion für den Vektor Shape 

shape_ptr find_shape(std::string const& eingabe, std::vector<std::shared_ptr<Shape>> const& shape_vector)
{
	auto it = find_if(shape_vector.begin(), shape_vector.end(),
		[&eingabe](std::shared_ptr<Shape> const& shape)
	{return (shape->name_) == eingabe; }
	);

	if (it != shape_vector.end())
		//wenn es nicht am Ende ist, dann wurde was gefunden, das soll zurückgegeben werden 
	{
		std::cout << "Shape " << eingabe << " exists." << endl;
		return *it;
		//* dereferenziert den pointer des iterators und gibt den shared_pointer zurück 
	}
	else
	{
		std::cout << "Shape " << eingabe << " doesn't exists." << endl;
		return nullptr;
	}
}