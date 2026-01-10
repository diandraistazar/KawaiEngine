#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define PROGRAM "KawaiEngine"
#define VERSION "v1.0"

enum { RET_SUCCESS, RET_FAILURE };
enum { M_SUCCESS, M_WARNING, M_ERROR, M_INFO };
enum { V_PLANE, V_TRIANGLE, V_LIGHT, V_TOTAL };
