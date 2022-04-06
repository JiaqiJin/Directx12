#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <cmath>

namespace Kawaii
{
#define PI 3.141592653589793238462643383279f

	// Vector
	typedef glm::vec2 Vector2f;
	typedef glm::vec3 Vector3f;
	typedef glm::vec4 Vector4f;

	typedef glm::ivec2 Vector2i;
	typedef glm::ivec3 Vector3i;
	typedef glm::ivec4 Vector4i;

	// Matrix
	typedef glm::mat3 Matrix3f;
	typedef glm::mat4 Matrix4f;

	typedef glm::mat<3, 3, int, glm::defaultp> Matrix3i;
	typedef glm::mat<4, 4, int, glm::defaultp> Matrix4i;

	// Quaternion
	typedef glm::quat Quternion;

}