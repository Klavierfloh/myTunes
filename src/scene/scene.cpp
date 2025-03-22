#include "../../include/scene/scene.h"

Scene::Scene()
{
    cerr << "SceneNotDefinedCorrectly" << endl;
}

Scene::Scene(const EventBus &eventBus) : GameObject(this)
{
    bus = eventBus;
    bus.registerListener("playMusic", this);
    bus.registerListener("pauseMusic", this);
    bus.registerListener("stopMusic", this);
    bus.registerListener("resumeMusic", this);
}

void Scene::addObject(GameObject *obj)
{
    std::cout << "Added Object" << endl;
    gameObjects.push_back(obj);
    return;
}

void Scene::process() 
{
    int size = gameObjects.size();
    for (int i = 0; i < size; i++)
    {
        gameObjects[i]->process();
    }
}

void Scene::render() 
{
    int size = gameObjects.size();
    for (int i = 0; i < size; i++)
    {
        gameObjects[i]->render();
    }
}

void Scene::event(string eventString, string eventObject) 
{
    if (eventString == "playMusic")
    {
        musicPlayer.changeMusic(eventObject);
    }
    else if (eventString == "pauseMusic")
    {
        musicPlayer.pause();
    }
    else if (eventString == "stopMusic")
    {
        musicPlayer.stop();
    }
    else if (eventString == "resumeMusic")
    {
        musicPlayer.resume();
    }
}

MusicPlayer& Scene::getMusicPlayer()
{
    return musicPlayer;
}

EventBus& Scene::getEventBus()
{
    return bus;
}
