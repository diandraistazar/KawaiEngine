#pragma once

#include "glm_math.hpp"

struct Light{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 intensity;
	glm::vec3 ambient;
	glm::vec3 specular;
};

struct Material{
	glm::vec3 ambient;
	glm::vec3 specular;
};

