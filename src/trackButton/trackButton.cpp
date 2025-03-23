#include "../../include/trackButtons/trackButton.h"
#include <raylib.h>
#include "../../include/scene/scene.h"
#include "../../include/utils.h"

TrackButton::TrackButton(Scene *scene, int pox, int poy, int wit, int heit, std::string trackPathL)
    : GameObject(scene), posx(pox), posy(poy), width(wit), height(heit), trackPath(trackPathL), trackName(get<2>(parseMusicPath(trackPath))){}

void TrackButton::process()
{
    Vector2 mouse = GetMousePosition();
    if (mouse.x > posx && mouse.x < posx + width && mouse.y > posy && mouse.y < posy + height && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
    scene->getEventBus().event("playMusic", trackPath);
    }
}
 
void TrackButton::render()
{
    DrawRectangle(posx,posy,width,height,YELLOW);
    DrawText(trackName.c_str(), posx,posy,15,BLACK);
}
 
void TrackButton::event(std::string eventString, std::string eventObject){}