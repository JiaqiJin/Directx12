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

    template<class T>
    T* AddComponent()
    {
        T* component = new T();
        rttr::type t = rttr::type::get(*component);
        std::string component_type_name = t.get_name().to_string();
        component->SetGameObject(this);

        // TODO
        return component;
    }
private:
    std::string name;
    std::unordered_map<std::string, std::vector<Component*>> component_type_instance_map;
};

#endif