#include "../../include/button/button.h"

Button::Button()
{
    std::cerr << "Button wrongly set up!" << std::endl;
}

Button::Button(Scene* scene, int pox, int poy, int wih, int heit, int buttonTyp)
    : GameObject(scene), posx(pox), posy(poy), width(wih), height(heit), buttonType(buttonTyp)
{
    switch (buttonType)
    {
    case STARTBUTTON:
        mainColor = GREEN;
        text = "START";
        break;

    case STOPBUTTON:
        mainColor = RED;
        text = "STOP";
        break;

    case PAUSEBUTTON:
        mainColor = BLUE;
        text = "PAUSE";
        break;

    case RESUMEBUTTON:
        mainColor = ORANGE;
        text = "RESUME";
        break;

    default:
        mainColor = GRAY;
        text = "UNKNOWN";
        break;
    }
}

void Button::buttonPressed()
{
    if (!scene) return;

    switch (buttonType)
    {
    case STARTBUTTON:
        scene->getEventBus().event("playMusic", ".\\Florence + The Machine - Bedroom Hymns.mp3");
        break;

    case PAUSEBUTTON:
        scene->getEventBus().event("pauseMusic", "");
        break;

    case STOPBUTTON:
        scene->getEventBus().event("stopMusic", "");
        break;

    case RESUMEBUTTON:
        scene->getEventBus().event("resumeMusic", "");
        break;

    default:
        break;
    }
}

void Button::process()
{
    Vector2 mouse = GetMousePosition();
    if (mouse.x > posx && mouse.x < posx + width && mouse.y > posy && mouse.y < posy + height && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        buttonPressed();
    }
}

void Button::render()
{
    DrawRectangle(posx, posy, width, height, mainColor);
    DrawText(text.c_str(), posx + 5, posy + height / 2 - 10, 20, BLACK);
}

void Button::event(std::string eventString, std::string eventObject)
{
    // No implementation yet
}
