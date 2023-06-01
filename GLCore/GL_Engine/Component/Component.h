#ifndef UNTITLED_COMPONENT_H
#define UNTITLED_COMPONENT_H

class GameObject;
class Component {
public:
    Component();
    virtual ~Component();

    GameObject* GetGameObject() { return game_object; }
    void SetGameObject(GameObject* _game_object) { game_object = _game_object; }
private:
    GameObject* game_object;
};


#endif //UNTITLED_COMPONENT_H