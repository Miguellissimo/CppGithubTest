#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "trivial.h"
#include "yaml.h"

int main() {

	YAML::Node config = YAML::LoadFile("config.yaml");
	if (config["name"]) {
		std::cout << "name: " << config["name"].as<std::string>() << "\n";
	}

	primitives p1 = {1, 2.0, {3, 4}};
	std::cout << "p.x has the value: " << p1.x << std::endl;

	return 0;
}

