#include "../../include/albumBox/albumBox.h"
#include "../../include/utils.h"

Box::Box(Scene *scene, int pox, int poy, int wih, int heit, std::string path)
    : GameObject(scene), posx(pox), posy(poy), width(wih), height(heit), path(path),headSize(0), parsedMusicPath(path)
{
    scene->getEventBus().registerListener("mouseWheelMoved", this);
    scene->getEventBus().registerListener("headSizeSet", this);
}

Box::Box() {}
void Box::render()
{
    Color c = RED;
    if (clicked)
    {
        c = GREEN;
    }
    DrawRectangle(posx, posy, width, height, c);
    DrawText(parsedMusicPath.c_str(), posx, posy, 10, BLACK);
}
void Box::process()
{

    Vector2 mouse = GetMousePosition();
    if (mouse.y>headSize && mouse.x > posx &&  mouse.x < posx + width && mouse.y > posy && mouse.y < posy + height && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        scene->getEventBus().event("openAlbum", parsedMusicPath);
        cout << "Opening Album "<<parsedMusicPath <<"\n";
    }
}

void Box::event(std::string eventString, std::string eventObject)
{
    if (eventString == "mouseWheelMoved")
    {
        posy += 10*stoi(eventObject);
        return;
    }
    if (eventString == "headSizeSet")
    {
        cout << "caught Size \n"; 
        headSize = stoi(eventObject);
        return;
    }
}