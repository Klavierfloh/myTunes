#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <iostream>
#include "../../include/constDefinitions.h"
#include "../../include/scene/scene.h"
#include "raylib.h"

class Button : public GameObject
{
private:
    int posx;
    int posy;
    int width;
    int height;
    int buttonType;
    std::string text;
    Color mainColor;

    void buttonPressed();

public:
    Button();
    Button(Scene* scene, int pox, int poy, int wih, int heit, int buttonTyp);

    void process() override;
    void render() override;
    void event(std::string eventString, std::string eventObject) override;
};

#endif  // BUTTON_H
