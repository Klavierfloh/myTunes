#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include <string>
using namespace std;

class Scene;

class GameObject
{
private:
public:
    Scene *scene;
    GameObject()
    {
        cerr << "SetGameObjectScene" << endl;
    }
    GameObject(Scene *sceneArg)
    {
        scene = sceneArg;
    }

    virtual void process() {}

    virtual void render() {}

    virtual void event(string eventString, string eventObject) {}
};

#endif