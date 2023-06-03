#include "Transfrom.h"
#include <rttr/registration>

using namespace rttr;

RTTR_REGISTRATION // registration reflection
{
	rttr::registration::class_<Transform>("Transform")
		.constructor<>()(rttr::policy::ctor::as_raw_ptr)
		.property("position", &Transform::GetPosition, &Transform::SetPosition)
		.property("rotation", &Transform::GetRotation, &Transform::SetRotation)
		.property("scale", &Transform::GetScale, &Transform::SetScale);
}

Transform::Transform()
	: position(0.f), rotation(0.f), scale(1.f)
{

}

Transform::~Transform()
{

}