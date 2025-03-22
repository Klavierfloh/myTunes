#ifndef ALBUMBOX_H
#define ALBUMBOX_H
#include "../../include/gameObject/gameObject.h"
#include <string>
#include "../../include/scene/scene.h"
#include <raylib.h>
class Box : public GameObject
{
private:
    int posx;
    int posy;
    int width;
    int height;
    float timePlayed = 0.0f;
    Music music;
    bool clicked = false;
    std::string path;
    int headSize;
    std::tuple<std::string, std::string, std::string> parsedMusicPath;

public:
    Box();
    Box(Scene *scene, int pox, int poy, int wih, int heit, std::string path);

    void render() override;

    void process() override;

    void event(std::string eventString, std::string eventObject) override;
};

#endif