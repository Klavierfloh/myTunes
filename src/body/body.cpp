#include "../../include/body/body.h"
#include "../../include/libraryManager/libraryManager.h"
#include "raylib.h"
#include "raymath.h"
#include "../../include/albumBox/albumBox.h"

Body::Body(Scene *scene, int pox, int poy, int wit, int heit, LibraryManager *libman)
    : GameObject(scene), posx(pox), posy(poy), width(wit), height(heit)
{
    index = libman->getLibraryAlbumIndex();
    using namespace std;
    int widthBut = 100;
    int maxWidthInButtons = (width- 120) / widthBut;

    albumBoxes.clear();
    for (int i = 0; i < (int)(index->size()); i++)
    {
        int level = i / (maxWidthInButtons);
        int posxB = 20 + posx + (i * widthBut) + 20 * i - ((level) * (width- 120 + widthBut));
        int posyB = posy + 20 + ((level)*widthBut) + 20 * (level - 1);
        Box *b = new Box(scene, posxB, posyB, widthBut, widthBut, (*index)[i]);
        albumBoxes.push_back(b);
    }
}
Body::~Body()
{
    albumBoxes.clear();
}

void Body::render()
{
    DrawRectangle(posx,posy,width,height,LIGHTGRAY);
    for (auto album : albumBoxes)
    {
        album->render();
    }
}
void Body::process()
{
    Vector2 mouse = GetMousePosition();
    if (mouse.x > posx && mouse.x < posx + width && mouse.y > posy && mouse.y < posy + height)
    {
        isHovered = true;
    }
    else
        isHovered = false;

    for (auto album : albumBoxes)
    {
        if (!isHovered)
        {
            album->lockScroll();
        }
        else
            album->unlockScroll();
        album->process();
    }
}

bool Body::getIsHovered()
{
    return isHovered;
}