#ifndef UNTITLED_TRANSFORM_H
#define UNTITLED_TRANSFORM_H

#include "Component.h"
#include <glm/glm.hpp>

class Transform : public Component 
{
public:
    Transform();
    ~Transform();

    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetRotation() const { return rotation; }
    glm::vec3 GetScale() const { return scale; }

    void SetPosition(glm::vec3 _position) { position = _position; }
    void SetRotation(glm::vec3 _rotation) { rotation = _rotation; }
    void SetScale(glm::vec3 _scale) { scale = _scale; }

private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

#endif //UNTITLED_TRANSFORM_H