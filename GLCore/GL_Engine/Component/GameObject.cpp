#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{

}

GameObject::GameObject(std::string name)
{
	SetName(name);
}

GameObject::~GameObject()
{

}

Component* GameObject::AddComponent(std::string component_type_name)
{
	rttr::type t = rttr::type::get_by_name(component_type_name);
	rttr::variant var = t.create();
	Component* component = var.get_value<Component*>();
	component->SetGameObject(this);

    if (component_type_instance_map.find(component_type_name) == component_type_instance_map.end()) {
        std::vector<Component*> component_vec;
        component_vec.push_back(component);
        component_type_instance_map[component_type_name] = component_vec;
    }
    else
    {
        component_type_instance_map[component_type_name].push_back(component);
    }

    return component;
}

Component* GameObject::GetComponent(std::string component_type_name)
{
    if (component_type_instance_map.find(component_type_name) == component_type_instance_map.end())
    {
        return nullptr;
    }

    if (component_type_instance_map[component_type_name].size() == 0) 
    {
        return nullptr;
    }

    return component_type_instance_map[component_type_name][0];
}

std::vector<Component*>& GameObject::GetComponents(std::string component_type_name)
{
    return component_type_instance_map[component_type_name];
}