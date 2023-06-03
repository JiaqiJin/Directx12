#ifndef UNTITLED_GAME_OBJECT_H
#define UNTITLED_GAME_OBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <rttr/registration.h>

class Component;

class GameObject
{
public:
    GameObject();
    GameObject(std::string name);
    ~GameObject();

    std::string& GetName() { return name; }
    void SetName(std::string name) { name = name; }

    Component* AddComponent(std::string component_type_name);

    template<class T>
    T* AddComponent()
    {
        T* component = new T();
        rttr::type t = rttr::type::get(*component);
        std::string component_type_name = t.get_name().to_string();
        component->SetGameObject(this);

        if (component_type_instance_map.find(component_type_name) == component_type_instance_map.end())
        {
            std::vector<Component*> components;
            components.push_back(component);
            component_type_instance_map[component_type_name] = components;
        }
        else
        {
            component_type_instance_map[component_type_name].push_back(component);
        }
       
        return component;
    }
    
    Component* GetComponent(std::string component_type_name);

    std::vector<Component*>& GetComponents(std::string component_type_name);
private:
    std::string name;
    std::unordered_map<std::string, std::vector<Component*>> component_type_instance_map;
};

#endif