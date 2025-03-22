#ifndef SCENE_H
#define SCENE_H
#include "../../include/gameObject/gameObject.h"
#include <vector>
#include "../../include/eventBus/eventBus.h"
#include "../../include/musicPlayer/musicPlayer.h"

class Scene : GameObject
{
private:
    vector<GameObject *> gameObjects = {};
    EventBus bus;
    MusicPlayer musicPlayer = MusicPlayer();

public:
    Scene();

    Scene(const EventBus &eventBus);

    void addObject(GameObject *obj);

    void process() override;

    void render() override;

    void event(string eventString, string eventObject) override;

    MusicPlayer &getMusicPlayer();

    EventBus &getEventBus();
};

#endif